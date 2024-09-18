#ifndef START_EVENT_LISTENER_H_
	#define START_EVENT_LISTENER_H_

#include "event_listener.h"
#include "irc_server.h"

class IrcServer;

class StartEventListener: public EventListener{
	public:
		StartEventListener(IrcServer& ircServer);
		~StartEventListener();
		EventListener*	accept(int fd);
		std::map<int, std::string> PassCommand(Event event);
		std::map<int, std::string> NickCommand(Event event);
		std::map<int, std::string> UserCommand(Event event);
		std::map<int, std::string> JoinCommand(Event event);
		std::map<int, std::string> InviteCommand(Event event);
		std::map<int, std::string> KickCommand(Event event);
		std::map<int, std::string> TopicCommand(Event event);
		std::map<int, std::string> PrivmsgCommand(Event event);
		std::map<int, std::string> ModeCommand(Event event);

	private:
		IrcServer& irc_server_;
};

#endif
