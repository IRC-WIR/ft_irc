#include "event_handler.h"
#include "command.h"
#include "channel.h"
#include "channel_event.h"

const	int	EventHandler::kQueueLimit = 10;
const	int EventHandler::kBufferSize = 512;
const	std::string EventHandler::kPollErrMsg = "poll failed";

EventHandler::~EventHandler() {
	return ;
}

EventHandler::EventHandler(Database& database,int port_no)
	: database_(database) {
	listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket_ < 0)
		std::exit(EXIT_FAILURE);
	if (fcntl(listening_socket_, F_SETFL, O_NONBLOCK) < 0)
		std::exit(EXIT_FAILURE);
	int option_available = 1;
	if (setsockopt(listening_socket_, SOL_SOCKET, SO_REUSEADDR, &option_available, sizeof(option_available)) < 0)
		std::exit(EXIT_FAILURE);
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
	if (pollResult < 0)
		throw (EventHandlerException(kPollErrMsg));
	if (pollResult == 0) {
		std::cout << "no event in 1000ms" << std::endl;
		return;
	}
	int fd_size = poll_fd_.size();
	for (int i = 0; i < fd_size; i++)
		HandlePollInEvent(this->poll_fd_[i]);
	for (int i = 0; i < fd_size; i++)
		HandlePollHupEvent(this->poll_fd_[i]);
	for (int i = 0; i < fd_size; i++)
		HandlePollOutEvent(this->poll_fd_[i]);
	return ;
}

void	EventHandler::HandlePollInEvent(pollfd entry) {
	if (entry.revents& (POLLIN))
	{
		if (entry.fd == listening_socket_) {
			Accept();
			return;
		}
		//receive用のbufferを作成し、null埋めする
		char receive_buffer[kBufferSize + 1];
		std::memset(receive_buffer, 0, kBufferSize + 1);
		recv(entry.fd, receive_buffer, kBufferSize, 0);
		std::cout << "[ "<< entry.fd << " ]Message from client: " << receive_buffer << std::endl;
		Execute(entry, receive_buffer);
	}
}

void	EventHandler::HandlePollOutEvent(pollfd entry) {
	if (entry.revents & POLLOUT) {
		int target_fd = entry.fd;
		if (response_map_[target_fd].empty())
			return ;
		for (std::vector<std::string>::iterator it = response_map_[target_fd].begin();
				it != response_map_[target_fd].end();) {
			const char *res_msg_char = (*it).c_str();
			int	res_msg_length = (*it).length();
			int sent_msg_length = send(target_fd, res_msg_char, res_msg_length, 0);

			//一部のみ送信成功
			if (sent_msg_length > 0 && sent_msg_length < res_msg_length) {
				*it = (*it).substr(sent_msg_length);
				continue;
			}
			//送信失敗
			if (sent_msg_length < 0) {
				Event* event = new Event(entry.fd, entry.revents);
				event->set_command(Command::kQuit);
				ExecuteCommand(event);
				delete event;
				return;
			}
			it = response_map_[target_fd].erase(it);
		}
		//対象ソケットへの、メッセージを送信し切った場合
		if (response_map_[target_fd].empty())
			std::cout << "all send from Database::response_map_" << std::endl;
	}
	return ;
}

void	EventHandler::HandlePollHupEvent(pollfd entry) {
	if (entry.revents & (POLLHUP)) {
		std::cout << entry.fd << ">> disconnected" << std::endl;
		Event* event = new Event(entry.fd, POLLHUP);
		event->set_command(Command::kQuit);
		ExecuteCommand(event);
		delete event;
	}
}

void	EventHandler::Detach(int fd) {
	std::cout << "connection hang up " << fd << std::endl;
	response_map_.erase(fd);
	for (std::vector<struct pollfd>::iterator it = poll_fd_.begin(); it != poll_fd_.end(); ++it) {
		if (it->fd == fd) {
			close(it->fd);
			poll_fd_.erase(it);
			return ;
		}
	}
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


void	EventHandler::Accept() {
	socklen_t server_address_len = (socklen_t)sizeof(server_address_);
	int connected_socket_ = accept(listening_socket_,
			(struct sockaddr*)&(server_address_),
			&server_address_len);
	if (connected_socket_ == -1)
			return;
	if (fcntl(listening_socket_, F_SETFL, O_NONBLOCK) < 0)
		std::exit(EXIT_FAILURE);
	std::cout << ">> NEW CONNECTION [ " << connected_socket_ << " ]" << std::endl;
	AddEventSocket(connected_socket_);
	database_.CreateUser(connected_socket_);
	return;
}

void	EventHandler::Execute(const pollfd& entry, const std::string& msg) {
	//EOFの場合
	if (msg[0] == '\0') {
		Event* event = new Event(entry.fd, POLLHUP);
		event->set_command(Command::kQuit);
		ExecuteCommand(event);
		delete event;
		return ;
	}
	std::string request_buffer;
	//prepare request_buffer
	//find request fd's remain msg
	std::map<int, std::string>::iterator req_it = request_map_.find(entry.fd);
	if (req_it != request_map_.end()) {
		request_buffer += req_it->second;
		request_map_.erase(req_it);
	}
	request_buffer += msg;

	std::string parsing_msg;
	std::string remain_msg;
	//request_buffer:
	//pattern1:command1\ncommand2\ncommand3\n
	while (utils::HasNewlines(request_buffer)) {
		parsing_msg = utils::TrimBefore(request_buffer, "\n");
		parsing_msg += "\n";
		remain_msg = utils::TrimAfter(request_buffer, "\n");
		//eventを作成
		Event* event = new Event(entry.fd, entry.revents);
		//parse
		MessageParser::ParseState parse_state = Parse(parsing_msg, *event);
		//debug print parse
		std::cout << "command:" << event->get_command().get_name() << std::endl;
		std::cout << "command param:" << std::endl;
		utils::PrintStringVector(event->get_command_params());
		//debug
		//judge parse result
		switch (parse_state) {
		case MessageParser::kParseError:
			std::cout << "Parse Error" <<std::endl;
			break ;
		case MessageParser::kParseNotAscii:
			//have to define the action of inputting out range of Ascii
			std::cout << "Not Ascii code input" << std::endl;
			break;
		case MessageParser::kParseEmpty:
			//have to define the action of emmpty inputting
			std::cout << "Parse Empty" <<std::endl;
			break ;
		default:
			this->ExecuteCommand(event);
			break ;
		}
		bool ret_flag = false;
		if (!event->HasErrorOccurred() && event->get_command() == Command::kQuit)
			ret_flag = true;
		delete event;
		if (ret_flag)
			return ;
		request_buffer = remain_msg;
	}
	if (!request_buffer.empty())
		request_map_.insert(std::make_pair(entry.fd, request_buffer));
}

void EventHandler::ExecuteCommand(Event*& event_ptr) {
	try {
		database_.CheckEvent(event_ptr);
		if (event_ptr->is_do_nothing())
			return ;
		if (EventHandler::CheckNewChannel(*event_ptr))
			this->AddNewChannel(event_ptr);
		AddResponseMap(database_.ExecuteEvent(*event_ptr));
		database_.DeleteFinishedElements();
		if (!event_ptr->HasErrorOccurred() && event_ptr->get_command() == Command::kQuit)
			Detach(event_ptr->get_fd());
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

bool EventHandler::CheckNewChannel(const Event& event) {
	return (!event.HasErrorOccurred()
			&& event.get_command() == Command::kJoin
			&& !event.IsChannelEvent());
}

void EventHandler::AddNewChannel(Event*& event_ptr) {
	const User& op = event_ptr->get_executer();
	const std::string& name = event_ptr->get_command_params()[0];
	const Channel& channel = this->database_.CreateChannel(op, name);
	ChannelEvent* channel_event = new ChannelEvent(*event_ptr, channel);
	delete event_ptr;
	event_ptr = channel_event;
}

MessageParser::ParseState	EventHandler::Parse(const std::string& buffer, Event &event) {
	std::string str_buffer(buffer);
	MessageParser message_parser(str_buffer);

	event.set_command(message_parser.get_command());
	event.set_command_params(message_parser.get_params());
	return message_parser.get_state();
}

void	EventHandler::Send(Event event) {
	(void)event;
	return ;
}

void	EventHandler::AddEventSocket(int new_fd) {
	pollfd new_pollfd;
	new_pollfd.fd = new_fd;
	new_pollfd.events = POLLIN | POLLOUT;
	new_pollfd.revents = 0;
	poll_fd_.push_back(new_pollfd);
}

void	EventHandler::AddResponseMap(std::map<int, std::string> new_response) {

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

EventHandler::EventHandlerException::EventHandlerException(const std::string& msg) : std::invalid_argument(msg){};
