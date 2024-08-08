#ifndef EVENT_HANDLER_H_
# define EVENT_HANDLER_H_

#include <map>
#include <poll.h>
#include "event_listener.h"

class EventHandler{
	public:
		EventHandler();
		EventHandler(EventListener& start_event_listener, EventListener& end_event_listener);
		~EventHandler();
		bool	IsListeningSocket();
		void	ExecutePoll();
		void	Accept(Event event);
		std::string Receive(Event event);
		void	Send(Event event);
		void	Detach(Event event);

	private:
		std::vector<EventListener>	event_listeners_;
		EventListener& start_event_listener_;
		EventListener& end_event_listener_;
		std::vector<struct poll_fd>	poll_fd_;
		std::map<int, std::string>	response_map_;
		int	listening_socket_;
};

#endif