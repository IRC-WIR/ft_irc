#include "event_handler.h"
#include <errno.h>

const	int	EventHandler::kQueueLimit = 10;
const	int EventHandler::kBufferSize = 512;
const	std::string EventHandler::kPollErrMsg = "poll failed";

EventHandler::~EventHandler() {
	return ;
}

EventHandler::EventHandler(Database& database,int port_no) : database_(database) {
	listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);

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

void	EventHandler::ExecutePoll() {
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
	{
		//bebug
		std::cerr << strerror(errno) << std::endl;
		throw (eventHandlerException(kPollErrMsg));
	}
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
		HandlePollInEvent(entry);
		HandlePollHupEvent(entry);
	}
	return ;
}

void	EventHandler::HandlePollInEvent(pollfd entry) {
	if (entry.revents& (POLLIN))
	{
		if (entry.fd == listening_socket_)
		{
			Accept();
			return ;
		}
		//receive用のbufferを作成し、null埋めする
		char receive_buffer[kBufferSize + 1];
		std::memset(receive_buffer, 0, kBufferSize + 1);
		Receive(entry.fd, receive_buffer);
		if (receive_buffer[0] == '\0')
			Detach(entry);
		std::cout << "[ "<< entry.fd << " ]Message from client: " << receive_buffer << std::endl;
		Execute(entry, receive_buffer);
	}
}

void	EventHandler::HandlePollOutEvent(pollfd entry) {
	(void)entry;
	return ;
}

void	EventHandler::HandlePollHupEvent(pollfd entry) {
	if (entry.revents& (POLLHUP))
	{
		std::cout << entry.fd << ">> disconnected" << std::endl;
	}
}

void	EventHandler::Detach(pollfd event) {
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

void	EventHandler::WaitMillSecond(int ms) {
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

int	EventHandler::Accept() {
	socklen_t server_address_len = (socklen_t)sizeof(server_address_);
	int connected_socket_ = accept(listening_socket_,
			(struct sockaddr*)&(server_address_),
			&server_address_len);
	if (connected_socket_ == -1)
		return -1;
	std::cout << ">> NEW CONNECTION [ " << connected_socket_ << " ]" << std::endl;
	add_event_socket(connected_socket_);
	database_.CreateUser(connected_socket_);
	return 0;
}

void	EventHandler::Receive(int fd, char* buffer) {
	//receive the message from the socket
	recv(fd, buffer, kBufferSize, 0);
	std::cout << "<Receive> " << buffer << std::endl;
}


void	EventHandler::Execute(const pollfd& entry, const std::string& msg) {
	std::string request_buffer;
	//find request fd's remain msg
	std::map<int, std::string>::iterator req_it = request_map_.find(entry.fd);
	if (req_it != request_map_.end())
	{
		request_buffer += req_it->second;
		req_it->second.clear();
	}
	//add receive buffer to request_buffer;
	request_buffer += msg;
	//prepare parsing message
	std::string parsing_msg = utils::ft_split_before(request_buffer, "\n");
	if (parsing_msg.empty())
	{
		//erase the request_buffer like "\n"
		utils::erase_newline(request_buffer);
		if (req_it != request_map_.end())
			req_it->second += request_buffer;
		else
			request_map_.insert(std::make_pair(entry.fd, request_buffer));
		return ;
	}
	//finish prepare parsing message
	//eventを作成
	Event event = Event(entry.fd, entry.revents);
	//parse
	message::ParseState parse_state = Parse(parsing_msg, event);
	//judge parse result
	switch (parse_state)
	{
		case message::kParseError:
			std::cout << "Parse Error" <<std::endl;
			break ;
		case message::KParseNotAscii:
			//have to define the action of inputting out range of Ascii
			std::cout << "Not Ascii code input" << std::endl;
			break;
		case message::kParseEmpty:
			//have to define the action of emmpty inputting
			std::cout << "Parse Empty" <<std::endl;
			break ;
		default:
			database_.ExecuteEvent(event);
			std::string remain_str = utils::ft_split_after(request_buffer, "\n");
			if (remain_str.empty())
				break;
			if (req_it != request_map_.end())
				req_it -> second = remain_str;
			else
				request_map_.insert(std::make_pair(event.get_fd(), remain_str));
			break;
	}
}



message::ParseState	EventHandler::Parse(const std::string& buffer, Event &event) {
	std::string str_buffer(buffer);

	//何回コマンドを受け取ったかを「/r/n」をsplitで確認
	message::MessageParser message_parser(str_buffer);

	//debug
	std::cout << "------debug------" << std::endl;
	std::cout << "state: " << message_parser.get_state() << std::endl;
	std::cout << "command: " << message_parser.get_command() << std::endl;
	std::cout << "command params: ";
	utils::print_string_vector(message_parser.get_params());
	std::cout << "\n\n------debug------" << std::endl;
	//
	event.set_command(message_parser.get_command());
	event.set_command_params(message_parser.get_params());
	return message_parser.get_state();
}

void	EventHandler::Send(Event event) {
	(void)event;
	return ;
}

void	EventHandler::add_event_socket(int new_fd) {
	pollfd new_pollfd;
	new_pollfd.fd = new_fd;
	new_pollfd.events = POLLIN;
	new_pollfd.revents = 0;
	poll_fd_.push_back(new_pollfd);
}

EventHandler::eventHandlerException::eventHandlerException(const std::string& msg) : std::invalid_argument(msg){};
