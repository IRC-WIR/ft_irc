#include "event_handler.h"

const	int	EventHandler::kQueueLimit = 10;
const	int EventHandler::kBufferSize = 512;
const	std::string EventHandler::kPollErrMsg = "poll failed";

EventHandler::~EventHandler()
{
	return ;
}

static int	SetNonBlockingMode(int socket_fd){
	int ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	if (ret < 0){
		switch (errno)
		{
		case EWOULDBLOCK:
		case EINTR:
			SetNonBlockingMode(socket_fd);
		default:
			std::cout << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	return ret;
}

EventHandler::EventHandler(Database& database,int port_no) : database_(database)
{
	listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket_ < 0) {
		std::cout << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	SetNonBlockingMode(listening_socket_);
	struct pollfd listening_pollfd;
	listening_pollfd.fd = listening_socket_;
	listening_pollfd.events = POLLIN;
	listening_pollfd.revents = 0;

	poll_fd_.push_back(listening_pollfd);

	server_address_.sin_family = AF_INET;
	server_address_.sin_port = htons(port_no);
	server_address_.sin_addr.s_addr = INADDR_ANY;
	bind(listening_socket_, (struct sockaddr*)&(server_address_), sizeof(server_address_));
	//第２引数をメンバ変数に定数追加　適切な数は？
	listen(listening_socket_, kQueueLimit);
	std::cout << "listening socket: " << listening_socket_ << std::endl;
	std::cout << "port no         : " << port_no << std::endl;

	return;
}

void	EventHandler::ExecutePoll()
{
	int	pollResult = poll(poll_fd_.data(), poll_fd_.size(), 1000);
	//debug
	// std::cout << "-- pollfd --" << std::endl;
	// for (int i = 0; i < (int)poll_fd_.size(); i++)
	// {
	// 	std::cout << i << ": " << poll_fd_.at(i).fd << std::endl;
	// }
	//	std::cout << "-- listener --" << std::endl;
	//	std::cout << event_listeners_.size() << std::endl;
	//////
	if (pollResult < 0)
		throw (eventHandlerException(kPollErrMsg));
	if (pollResult == 0)
	{
		//debug
		std::cout << "no event in 1000ms" << std::endl;
		return;
	}
	int fd_size = poll_fd_.size();
	for (int i = 0; i < fd_size; i++)
	{
		pollfd entry = this->poll_fd_[i];
		HandlePollOutEvent(entry);
		HandlePollHupEvent(entry);
		HandlePollInEvent(entry);
	}
	return ;
}

void	EventHandler::HandlePollInEvent(pollfd entry)
{
	if (entry.revents& (POLLIN))
	{
		if (entry.fd == listening_socket_)
		{
			Accept();
			return;
		}
		//eventを作成
		Event event = Event(entry.fd, entry.revents);
		//bufferを作成し、null埋めする
		char buffer[kBufferSize + 1];
		std::memset(buffer, 0, kBufferSize + 1);
		Receive(event, buffer);
		if (buffer[0] == '\0')
			Detach(entry);
		std::cout << "[ "<< event.get_fd() << " ]Message from client: " << buffer << std::endl;
		message::ParseState parse_state = Parse(buffer, event);
		if (parse_state == message::kParseError)
			return ;
		//debug
		if (parse_state == message::KParseNotAscii)
		{
			std::cout << "Not Ascii code input" << std::endl;
			return;
		}
		//
		database_.ExecuteEvent(event);
		std::cout << "test2" << std::endl;
		database_.DeleteFinishedElements();
		std::cout << "test3" << std::endl;
	}
}

void	EventHandler::HandlePollOutEvent(pollfd entry)
{
	if (entry.revents & POLLOUT)
	{
		int target_fd = entry.fd;
    for (std::vector<std::string>::iterator it = response_map_[target_fd].begin();
			it != response_map_[target_fd].end();) {
			const char *res_msg_char = (*it).c_str();
			int	res_msg_length = (*it).length();
			int sent_msg_length = send(target_fd, res_msg_char, res_msg_length, 0);
			
			//メッセージ全体の送信に失敗
			if (sent_msg_length < res_msg_length) {

				switch (errno) {
				//プログラム終了
				case EFAULT:
				case EMSGSIZE:
					std::cout <<  strerror(errno) << std::endl;
    			exit(EXIT_FAILURE);
				//次回POLLOUT発生時に再送
				case EWOULDBLOCK:
					if (sent_msg_length > 0)
						*it = (*it).substr(sent_msg_length);
					return;
				//直ちに再送
			  case EINTR:
					break ;
				//接続切断
				default:
					Detach(entry);
					Event event = Event(entry.fd, entry.revents); 
					event.set_command(message::kQuit);
					database_.ExecuteEvent(event);
					response_map_.erase(target_fd);	
					return;
				}
				continue;
			} else {
				it = response_map_[target_fd].erase(it);
			}
		}
		//対象ソケットへの、メッセージを送信し切った場合
		if (response_map_[target_fd].empty()){
			std::cout << "erase from Database::response_map_" << std::endl;
			response_map_.erase(target_fd);
		}
	}
	return ;
}

void	EventHandler::HandlePollHupEvent(pollfd entry)
{
	if (entry.revents& (POLLHUP))
	{
		std::cout << entry.fd << ">> disconnected" << std::endl;
	}
}

void	EventHandler::Detach(pollfd event)
{
	std::cout << "connection hang up " << event.fd << std::endl;
	int target_index = 0;
	for (int i = 0; i < (int)poll_fd_.size(); i++)
	{
		if (poll_fd_[i].fd == event.fd)
			target_index = i;
	}
	poll_fd_.erase(poll_fd_.begin() + target_index);
	return ;
}

void	EventHandler::WaitMillSecond(int ms)
{
	timeval start;
	timeval current;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		if ((current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000 >= ms)
			return ;
	}
}

void	EventHandler::Accept()
{
	socklen_t server_address_len = (socklen_t)sizeof(server_address_);
	int connected_socket_ = accept(listening_socket_,
			(struct sockaddr*)&(server_address_),
			&server_address_len);
	if (connected_socket_ == -1){
		switch (errno)
		{
		//接続リトライ
		case EWOULDBLOCK:
		case EINTR:
			break;
		//プログラム終了
		case EBADF:
		case EFAULT:
		case ECONNABORTED:
		case EINVAL:
		case ENOTSOCK:
		case EOPNOTSUPP:
			exit(EXIT_FAILURE);
		//接続不可
		default:
			return;
		}
	}
	SetNonBlockingMode(connected_socket_);
	std::cout << ">> NEW CONNECTION [ " << connected_socket_ << " ]" << std::endl;
	add_event_socket(connected_socket_);
	database_.CreateUser(connected_socket_);
	return;
}

void	EventHandler::Receive(Event event, char* buffer)
{
	//receive the message from the socket
	recv(event.get_fd(), buffer, kBufferSize, 0);
	std::cout << "<Receive> " << buffer << std::endl;
}

message::ParseState	EventHandler::Parse(const char *buffer, Event &event){
	std::string str_buffer(buffer);

	//何回コマンドを受け取ったかを「/r/n」をsplitで確認
	message::MessageParser message_parser(str_buffer);

//	//debug
//	std::cout << "------debug------" << std::endl;
//	std::cout << "state: " << message_parser.get_state() << std::endl;
//	std::cout << "command: " << message_parser.get_command() << std::endl;
//	std::cout << "command params: ";
//	utils::print_string_vector(message_parser.get_params());
//
//	std::cout << "\n\n------debug------" << std::endl;
//	//
	event.set_command(message_parser.get_command());
	event.set_command_params(message_parser.get_params());
	return message_parser.get_state();
}

void	EventHandler::Send(Event event)
{
	(void)event;
	return ;
}

void	EventHandler::add_event_socket(int new_fd)
{
	pollfd new_pollfd;
	new_pollfd.fd = new_fd;
	new_pollfd.events = POLLIN | POLLOUT;
	new_pollfd.revents = 0;
	poll_fd_.push_back(new_pollfd);
}

void	EventHandler::add_response_map(std::map<int, std::string> new_response){
	
	for (std::map<int, std::string>::iterator new_map_iterator =
		new_response.begin();
		new_map_iterator != new_response.end();
		new_map_iterator++){

		std::map<int, std::vector<std::string> >::iterator existing_map_iterator =
			this->response_map_.find(new_map_iterator->first);

		//該当fdに対して送信するメッセージが存在しない場合は新規pair追加
		if (existing_map_iterator == this->response_map_.end()){
			this->response_map_.insert(std::pair<int, std::vector<std::string> >
			(new_map_iterator->first, std::vector<std::string>(1, new_map_iterator->second)));

		//該当fdに対して送信するメッセージが存在する場合は要素のsecondに文字列を追加
		} else {
			existing_map_iterator->second.push_back(new_map_iterator->second);
		}
	}
}
EventHandler::eventHandlerException::eventHandlerException(const std::string& msg) : std::invalid_argument(msg){};
