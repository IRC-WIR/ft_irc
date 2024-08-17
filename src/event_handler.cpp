#include "event_handler.h"
#include "utils.h"

const	int	EventHandler::kQueueLimit = 10;

EventHandler::EventHandler(EventListener& start_event_listener, EventListener& end_event_listener, std::string port_no) : start_event_listener_(start_event_listener), end_event_listener_(end_event_listener)
{
	this->listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	this->server_address_.sin_family = AF_INET;

	this->server_address_.sin_port = htons(utils::ft_stoi(port_no));
	this->server_address_.sin_addr.s_addr = INADDR_ANY;

	bind(this->listening_socket_, (struct sockaddr*)&(this->server_address_), sizeof(this->server_address_));
	//第２引数をメンバ変数に定数追加　適切な数は？
	listen(this->listening_socket_, this->kQueueLimit);

	return;	
}

void	EventHandler::ExecutePoll()
{
	int	pollResult = poll(poll_fd_.data(), poll_fd_.size(), 1000);
	if (pollResult < 0) {
		perror("poll failed");
		return;
 	}
	if (pollResult == 0)
	{
		std::cout << "no event in 1000ms" << std::endl;
		return;
	}
	bool is_listening_socket;
	int fd_size = this->poll_fd_.size();
	for (int i = 0; i < fd_size; i++)
	{	
		pollfd entry = this->poll_fd_[i];
		if (entry.fd == listening_socket_)
			is_listening_socket = true;
		else
			is_listening_socket = false;
		if (entry.revents& (POLLIN))
		{
			Event event = Event(is_listening_socket, entry.fd, entry.revents);
			int event_listener_size = this->event_listeners_.size();
			for (int j = 0; j < event_listener_size; j++)
			{
				if (this->Accept(event) == 0)
				{
					fd_size++;
				}
				this->Receive(event);
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

