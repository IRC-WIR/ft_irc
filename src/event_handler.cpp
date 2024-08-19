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
	//only for now
	//reason: exception does not work at the time, and cannot set port_no
	port_no = "8080";

	listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);

	struct pollfd listening_pollfd;
	listening_pollfd.fd = listening_socket_;
	listening_pollfd.events = POLLIN;
	poll_fd_.push_back(listening_pollfd);

	server_address_.sin_family = AF_INET;
	server_address_.sin_port = htons(utils::ft_stoi(port_no));
	server_address_.sin_addr.s_addr = INADDR_ANY;
	bind(listening_socket_, (struct sockaddr*)&(server_address_), sizeof(server_address_));
	//第２引数をメンバ変数に定数追加　適切な数は？
	listen(listening_socket_, kQueueLimit);

	return;
}

void	EventHandler::ExecutePoll()
{
	int	pollResult = poll(poll_fd_.data(), poll_fd_.size(), 1000);
	if (pollResult < 0)
		throw (IrcServer::IrcException("poll failed"));
	if (pollResult == 0)
	{
		std::cout << "no event in 1000ms" << std::endl;
		return;
	}
	bool is_listening_socket;
	int fd_size = poll_fd_.size();
	std::cout << "out of for " << std::endl;
	for (int i = 0; i < fd_size; i++)
	{
		pollfd entry = this->poll_fd_[i];
		if (entry.fd == listening_socket_)
			is_listening_socket = true;
		else
			is_listening_socket = false;
		if (entry.revents& (POLLIN))
		{
			std::cout << "caught POLLIN event " << entry.fd << std::endl;
			Event event = Event(entry.fd, entry.revents);
			int event_listener_size = event_listeners_.size();
			if (event_listener_size == 0)
				Accept(event, is_listening_socket);
			for (int j = 0; j < event_listener_size; j++)
			{
				if (Accept(event, is_listening_socket) == 0)
				{
					fd_size++;
				}
				Receive(event);
			}
		}
		is_listening_socket = false;
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
};

int	EventHandler::Accept(Event event, bool is_listening_socket)
{
	std::cout << "Accept is called" << std::endl;
	if (is_listening_socket)
		std::cout << "is listening socket" << std::endl;
	else
		std::cout << "is NOT listening socket" << std::endl;
	(void)event;
	(void)is_listening_socket;
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
