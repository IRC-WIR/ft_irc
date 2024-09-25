#ifndef CHECK_H_
 # define CHECK_H_

#include "prepare_event_listener.h"

class Check: public PrepareEventListener{
	public:
		Check();
		~Check();
		std::map<int, std::string> PassCommand(Event& event);
		std::map<int, std::string> NickCommand(Event& event);
		std::map<int, std::string> UserCommand(Event& event);
		std::map<int, std::string> JoinCommand(Event& event);
		std::map<int, std::string> InviteCommand(Event& event);
		std::map<int, std::string> KickCommand(Event& event);
		std::map<int, std::string> TopicCommand(Event& event);
		std::map<int, std::string> ModeCommand(Event& event);
		std::map<int, std::string> PrivmsgCommand(Event& event);

	private:
};

#endif
