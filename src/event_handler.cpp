#include "event_handler.h"

EventHandler::EventHandler()
{

};

EventHandler::EventHandler(EventListener& startEventListener, EventListener& endEventListener)
{
	this->start_event_listener_ = startEventListener;
	this->end_event_listener_ = endEventListener;

	this->listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	this->server_address_.sin_family = AF_INET;
	this->server_address_.sin_port = htons(this->listening_socket_->port_no_);
	this->server_address_.sin_addr.s_addr = INADDR_ANY;

	bind(this->listening_socket_, (struct sockaddr*)&(this->server_address_), sizeof(this->server_address_));
	//第２引数をメンバ変数に定数追加　適切な数は？
	listen(this->listening_socket_, this->queue_limit_);

	return;	
}

void	EventHandler::ExecutePoll()
{
	// for debug
	std::cout << "Event sockets: ";
		for (const auto& socket : this->poll_fd_) {
			std::cout << socket.fd << " ";
		}
  	std::cout << std::endl;
	///

	int	pollResult = poll(this->poll_fd_.data(), this->poll_fd_.size(), 1000);
	if (pollResult < 0) {
		perror("poll failed");
		return;
 	}
	if (pollResult == 0)
	{
		std::cout << "no event in 1000ms" << std::endl;
		return;
	}
	bool is_listening_socket = true;
	int fd_size = this->poll_fd_.size();
	for (int i = 0; i < fd_size; i++)
	{	
		pollfd entry = this->poll_fd_[i];
		if (entry.revents& (POLLIN))
		{
			Event event = Event(entry.fd, entry.revents, is_listening_socket);
			int event_listener_size = this->event_listeners_.size();
			for (int j = 0; j < event_listener_size; j++)
			{
				EventListener * eventListener = this->event_listeners_[j];
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

