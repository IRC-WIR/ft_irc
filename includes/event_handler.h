#ifndef EVENT_HANDLER_H_
# define EVENT_HANDLER_H_

#include <poll.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include "message.h"
#include "event.h"
#include "database.h"

class EventHandler{
	public:
		EventHandler(Database& database,int port_no);
		~EventHandler();
		bool				IsListeningSocket();
		void				ExecutePoll();
		void				WaitMillSecond(int ms);
		void				add_event_socket(int new_fd);
		//ネスト例外クラス
		class EventHandlerException : public std::invalid_argument
		{
			public:
				EventHandlerException(const std::string& msg);
		};

	private:
		EventHandler();
		int					Accept();
		void				Receive(int fd, char* buffer);
		void				Execute(const pollfd& entry, const std::string& msg);
		message::ParseState	Parse(const std::string& buffer, Event& event);
		void				Send(Event event);
		void				Detach(pollfd entry);
		void				HandlePollInEvent(pollfd entry);
		void				HandlePollOutEvent(pollfd entry);
		void				HandlePollHupEvent(pollfd entry);

		Database&	database_;
		std::vector<struct pollfd>	poll_fd_;
		std::map<int, std::string>	response_map_;
		int	listening_socket_;
		sockaddr_in	server_address_;
		std::map<int, std::string>	request_map_;

		//定数
		static const int	kQueueLimit;
		static const int	kBufferSize;
		static const std::string kPollErrMsg;
};

#endif
