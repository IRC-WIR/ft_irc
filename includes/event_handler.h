#ifndef EVENT_HANDLER_H_
# define EVENT_HANDLER_H_

#include <poll.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "message.h"
#include "event.h"
#include "database.h"
#include "optional_message.h"

class EventHandler{
	public:
		EventHandler(Database& database,int port_no);
		~EventHandler();
		bool				IsListeningSocket();
		void				ExecutePoll();
		void				WaitMillSecond(int ms);
		void				add_event_socket(int new_fd);
		void				add_response_map(std::map<int, std::string> newResponse);
		//ネスト例外クラス
		class eventHandlerException : public std::invalid_argument
		{
			public:
				eventHandlerException(const std::string& msg);
		};

	private:
		EventHandler();
		void				Accept();
		void				Receive(Event event, char* buffer);
		message::ParseState	Parse(const char *buffer, Event& event);
		void				Send(Event event);
		void				Detach(pollfd entry);
		void				HandlePollInEvent(pollfd entry);
		void				HandlePollOutEvent(pollfd entry);
		void				HandlePollHupEvent(pollfd entry);

		Database&	database_;
		std::vector<struct pollfd>	poll_fd_;
		std::map<int, std::vector<std::string> >	response_map_;
		int	listening_socket_;
		sockaddr_in	server_address_;

		//定数
		static const int	kQueueLimit;
		static const int	kBufferSize;
		static const std::string kPollErrMsg;
};

#endif
