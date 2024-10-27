#ifndef EVENT_HANDLER_H_
# define EVENT_HANDLER_H_

#include <poll.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <cerrno>
#include <cstdlib>
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
		void				AddEventSocket(int new_fd);
		void				AddResponseMap(std::map<int, std::string> newResponse);
		//ネスト例外クラス
		class EventHandlerException : public std::invalid_argument
		{
			public:
				EventHandlerException(const std::string& msg);
		};

	private:
		EventHandler();
		void				Accept();
		void				Receive(int fd, char* buffer);
		void				Execute(const pollfd& entry, const std::string& msg);
		message::ParseState	Parse(const std::string& buffer, Event& event);
		void				Send(Event event);
		Event&				Detach(pollfd entry);
		void				HandlePollInEvent(pollfd entry);
		void				HandlePollOutEvent(pollfd entry);
		void				HandlePollHupEvent(pollfd entry);
		void				ExecuteCommand(Event& event);

		Database&	database_;
		std::vector<struct pollfd>	poll_fd_;
		std::map<int, std::vector<std::string> >	response_map_;
		int	listening_socket_;
		sockaddr_in	server_address_;
		std::map<int, std::string>	request_map_;

		//定数
		static const int	kQueueLimit;
		static const int	kBufferSize;
		static const std::string kPollErrMsg;
};

#endif
