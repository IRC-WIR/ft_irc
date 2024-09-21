#ifndef USER_H_
 #define USER_H_

#include "event_listener.h"

class Channel;

class User : public EventListener{
	public:
		User();
		User(int fd);
		~User();
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
		int	fd_;
		bool	is_password_authenticated_;
		std::string	nickname_;
		std::string	username_;
		std::vector<Channel>	channels_;
};

#endif
