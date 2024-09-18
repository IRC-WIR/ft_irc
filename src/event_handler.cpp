#include "event_handler.h"
#include "irc_server.h"

const	int	EventHandler::kQueueLimit = 10;
const	int EventHandler::kBufferSize = 512;

EventHandler::EventHandler()
{
	return ;
}

EventHandler::~EventHandler()
{
	return ;
}

EventHandler::EventHandler(StartEventListener* start_event_listener, EndEventListener* end_event_listener, std::string port_no) : start_event_listener_(start_event_listener), end_event_listener_(end_event_listener)
{
	listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);

	struct pollfd listening_pollfd;
	listening_pollfd.fd = listening_socket_;
	listening_pollfd.events = POLLIN;
	listening_pollfd.revents = 0;

	poll_fd_.push_back(listening_pollfd);

	server_address_.sin_family = AF_INET;
	server_address_.sin_port = htons(utils::ft_stoi(port_no));
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
		throw (IrcServer::IrcException("poll failed"));
	if (pollResult == 0)
	{
		//debug
		//std::cout << "no event in 1000ms" << std::endl;
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

void	EventHandler::HandlePollInEvent(pollfd entry)
{
	if (entry.revents& (POLLIN))
	{
		if (entry.fd == listening_socket_)
		{
			Accept();
			return ;
		}
		Event event = Event(entry.fd, entry.revents);
	//	message::Command command = Receive(event, entry);
	//	ExecuteCommand(command, event);
		char *buffer = Receive(event);
		if (buffer[0] == '\0')
			Detach(entry);
		//std::cout << "[ "<< event.get_fd() << " ]Message from client: " << buffer << std::endl;
		if (Parse(buffer, event) != message::PARSE_COMPLETE)
			return ;
		ExecuteCommand(event);
	}
}

void	EventHandler::ExecuteCommand(Event event){

	int listener_size = event_listeners_.size();
	for (int i = 0; i < listener_size; i++)

		switch (event.get_command()){

			case message::PASS:
				event_listeners_[i]->PassCommand(event);
				break;
			case message::NICK:
				event_listeners_[i]->NickCommand(event);
				break;
			case message::USER:
				event_listeners_[i]->UserCommand(event);
				break;
			case message::JOIN:
				event_listeners_[i]->JoinCommand(event);
				break;
			case message::INVITE:
				event_listeners_[i]->InviteCommand(event);
				break;
			case message::KICK:
				event_listeners_[i]->KickCommand(event);
				break;
			case message::TOPIC:
				event_listeners_[i]->TopicCommand(event);
				break;
			case message::MODE:
				event_listeners_[i]->ModeCommand(event);
				break;
			case message::PRIVMSG:
				event_listeners_[i]->PrivmsgCommand(event);
				break;
			default:
				return ;
		}
}

void	EventHandler::HandlePollOutEvent(pollfd entry)
{
	(void)entry;
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

int	EventHandler::Accept()
{
	socklen_t server_address_len = (socklen_t)sizeof(server_address_);
	int connected_socket_ = accept(listening_socket_,
			(struct sockaddr*)&(server_address_),
			&server_address_len);
	if (connected_socket_ == -1)
		return -1;
	std::cout << ">> NEW CONNECTION [ " << connected_socket_ << " ]" << std::endl;
	add_event_socket(connected_socket_);

	EventListener* event_listener = start_event_listener_->accept(connected_socket_);
	if (event_listener)
		event_listeners_.push_back(event_listener);
	return 0;
}

char	*EventHandler::Receive(Event event){

	char *buffer = (char *)malloc(sizeof(char) * this->kBufferSize);
	//char buffer[this->kBufferSize];
	bzero(buffer, sizeof(char) * this->kBufferSize);
	//receive the message from the socket
	recv(event.get_fd(), buffer, sizeof(buffer), 0);
	std::cout << "<Receive> " << buffer << std::endl; 
	return buffer;
}

message::ParseState	EventHandler::Parse(const char *buffer, Event &event){
	std::string str_buffer(buffer);
	message::MessageParser message_parser(str_buffer);
	std::cout << "<Parse> " << buffer <<", " << str_buffer << std::endl; 
	//debug
	std::cout << "------debug------" << std::endl;
	std::cout << "state: " << message_parser.get_state();
	std::cout << "command: " << message_parser.get_command();
	utils::print_string_vector(message_parser.get_params());
	std::cout << "------debug------" << std::endl;
	//
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
	new_pollfd.events = POLLIN;
	new_pollfd.revents = 0;
	poll_fd_.push_back(new_pollfd);
}

