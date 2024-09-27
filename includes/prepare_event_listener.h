#ifndef PREPARE_EVENT_LISTENER_H_
 #define PREPARE_EVENT_LISTENER_H_


#include "event_listener.h"

class PrepareEventListener
{
	public:
		PrepareEventListener();
		virtual ~PrepareEventListener();
		virtual std::map<int, std::string> PassCommand(Event& event) = 0;
		virtual std::map<int, std::string> NickCommand(Event& event) = 0;
		virtual std::map<int, std::string> UserCommand(Event& event) = 0;
		virtual std::map<int, std::string> JoinCommand(Event& event) = 0;
		virtual std::map<int, std::string> InviteCommand(Event& event) = 0;
		virtual std::map<int, std::string> KickCommand(Event& event) = 0;
		virtual std::map<int, std::string> TopicCommand(Event& event) = 0;
		virtual std::map<int, std::string> ModeCommand(Event& event) = 0;
		virtual std::map<int, std::string> PrivmsgCommand(Event& event) = 0;

	private:

};

#endif