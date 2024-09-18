#ifndef CHANNEL_H_
 # define CHANNEL_H_

#include "event_listener.h"
#include "user.h"

class User;

class Channel: public EventListener{
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
		std::vector<User>	users_;
		std::string		topic_;
		std::string		key_;
		std::string		name_;
		std::vector<User>	operators_;
		int	max_member_num_;
		bool	i_mode;
		bool	t_mode;
		bool	k_mode;
		bool	o_mode;
		bool	l_mode;
};

#endif
