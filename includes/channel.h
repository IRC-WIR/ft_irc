#ifndef CHANNEL_H_
 # define CHANNEL_H_

#include "event_listener.h"

class User;

class Channel: public EventListener{
	public:
		Channel();
		~Channel();
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
