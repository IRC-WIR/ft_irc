#include "event_handler.h"
#include "utils.h"
#include "irc_server.h"

const	int	EventHandler::kQueueLimit = 10;

EventHandler::EventHandler()
{
	return ;
}

EventHandler::~EventHandler()
{
	return ;
}

EventHandler::EventHandler(EventListener* start_event_listener, EventListener* end_event_listener, std::string port_no) : start_event_listener_(start_event_listener), end_event_listener_(end_event_listener)
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
	std::cout << "-- pollfd --" << std::endl;
	for (int i = 0; i < (int)poll_fd_.size(); i++)
	{
		std::cout << i << ": " << poll_fd_.at(i).fd << std::endl;
	}
	//////
	if (pollResult < 0)
		throw (IrcServer::IrcException("poll failed"));
	if (pollResult == 0)
	{
		std::cout << "no event in 1000ms" << std::endl;
		return;
	}
	int fd_size = poll_fd_.size();
	std::cout << "out of for " << std::endl;
	//インデントが深くならないように
	//POLLIN/POLLOUTハンドル用のメソッドに分ける？
	for (int i = 0; i < fd_size; i++)
	{
		pollfd entry = this->poll_fd_[i];
		if (entry.revents& (POLLIN))
		{
			std::cout << "caught POLLIN event " << entry.fd << std::endl;
			if (entry.fd == listening_socket_)
			{
				Accept();
				continue;
			}
			Event event = Event(entry.fd, entry.revents);
			int event_listener_size = event_listeners_.size();
			for (int j = 0; event_listener_size == 0 || j < event_listener_size; j++)
			{
				Receive(event);
			}
		}
	}
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
	std::cout << "Accept is called" << std::endl;
	socklen_t server_address_len = (socklen_t)sizeof(server_address_);
	int connected_socket_ = accept(listening_socket_,
			(struct sockaddr*)&(server_address_),
			&server_address_len);
	if (connected_socket_ == -1)
		return -1;
	// User newUser = User(connectedSocket,kACCEPTED,NULL);
	// this->users_.push_back(newUser);
	std::cout << ">> NEW CONNECTION [ " << connected_socket_ << " ]" << std::endl;
	add_event_socket(connected_socket_);
	return 0;
}

std::string	EventHandler::Receive(Event event)
{
	(void)event;
	return NULL;
}

void	EventHandler::Send(Event event)
{
	(void)event;
	return ;
}

void	EventHandler::Detach(Event event)
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
