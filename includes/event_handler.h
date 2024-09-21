#ifndef EVENT_HANDLER_H_
# define EVENT_HANDLER_H_

#include <poll.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include "event_listener.h"
#include "utils.h"
#include "message.h"

class StartEventListener;

class EndEventListener;

class EventHandler{
	public:
		EventHandler(StartEventListener* start_event_listener, EndEventListener* end_event_listener, std::string port_no);
		EventHandler();
		~EventHandler();
		bool				IsListeningSocket();
		void				ExecutePoll();
		void				WaitMillSecond(int ms);
		void				add_event_socket(int new_fd);

	private:
		int					Accept();
		void				Receive(Event event, char* buffer);
		message::ParseState	Parse(const char *buffer, Event& event);
		void				ExecuteCommand(Event event);
		void				CallStartEventListener(Event& event);
		void				CallEndEventListener(Event& event);
		void				Send(Event event);
		void				Detach(pollfd entry);
		void				HandlePollInEvent(pollfd entry);
		void				HandlePollOutEvent(pollfd entry);
		void				HandlePollHupEvent(pollfd entry);


		std::vector<EventListener *>	event_listeners_;
		StartEventListener* start_event_listener_;
		EndEventListener* end_event_listener_;
		std::vector<struct pollfd>	poll_fd_;
		std::map<int, std::string>	response_map_;
		int	listening_socket_;
		sockaddr_in	server_address_;

		//定数
		static const int	kQueueLimit;
		static const int	kBufferSize;
};

#endif
