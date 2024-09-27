#ifndef DELETE_EVENT_LISTENER_H_
	#define DELETE_EVENT_LISTENER_H_

#include "event_listener.h"
#include "irc_server.h"

class IrcServer;

class DeleteEventListener: public EventListener{
	public:
		DeleteEventListener(IrcServer& ircServer);
		~DeleteEventListener();
		std::map<int, std::string> PassCommand(const Event& event);
		std::map<int, std::string> NickCommand(const Event& event);
		std::map<int, std::string> UserCommand(const Event& event);
		std::map<int, std::string> JoinCommand(const Event& event);
		std::map<int, std::string> InviteCommand(const Event& event);
		std::map<int, std::string> KickCommand(const Event& event);
		std::map<int, std::string> TopicCommand(const Event& event);
		std::map<int, std::string> ModeCommand(const Event& event);
		std::map<int, std::string> PrivmsgCommand(const Event& event);

	private:
		IrcServer& irc_server_;
};

#endif
