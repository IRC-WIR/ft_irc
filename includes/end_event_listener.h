#ifndef END_EVENT_LISTENER_H_
	#define END_EVENT_LISTENER_H_

#include "event_listener.h"
#include "irc_server.h"

class IrcServer;

class EndEventListener: public EventListener{
	public:
		EndEventListener(IrcServer& ircServer);
		~EndEventListener();
		std::map<int, std::string> PassCommand(Event event);
		std::map<int, std::string> NickCommand(Event event);
		std::map<int, std::string> UserCommand(Event event);
		std::map<int, std::string> JoinCommand(Event event);
		std::map<int, std::string> InviteCommand(Event event);
		std::map<int, std::string> KickCommand(Event event);
		std::map<int, std::string> TopicCommand(Event event);
		std::map<int, std::string> ModeCommand(Event event);
		std::map<int, std::string> PrivmsgCommand(Event event);

	private:
		IrcServer& irc_server_;
};

#endif
