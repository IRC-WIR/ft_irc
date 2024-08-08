#ifndef START_EVENT_LISTENER_H_
	#define START_EVENT_LISTENER_H_

#include "event_listener.h"
#include "irc_server.h"

class StartEventListener: public EventListener{
	public:
		StartEventListener();
		~StartEventListener();
		std::map<int, std::string> Pass(Event event);
		std::map<int, std::string> Nick(Event event);
		std::map<int, std::string> Join(Event event);
		std::map<int, std::string> Invite(Event event);
		std::map<int, std::string> Kick(Event event);
		std::map<int, std::string> Topic(Event event);
		std::map<int, std::string> Part(Event event);
		std::map<int, std::string> Prvmsg(Event event);
		std::map<int, std::string> Quit(Event event);
		std::map<int, std::string> Mode(Event event);

	private:
		IrcServer& irc_server_;
};

#endif