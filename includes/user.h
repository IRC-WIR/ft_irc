#ifndef USER_H_
 #define USER_H_

#include "event_listener.h"
#include "channel.h"

class Channel;

class User : public EventListener{
	public:
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
		bool	is_password_authenticated_;
		std::string	nick_name_;
		std::string	user_name_;
		std::vector<Channel>	channels_;

};

#endif