#ifndef CHANNEL_H_
 # define CHANNEL_H_

#include "event_configurator.h"

class User;

class Channel: public EventConfigurator{
	public:
		Channel();
		~Channel();
		Event&	PreparePassCommand(const Event& event);
		Event&	PrepareNickCommand(const Event& event);
		Event&	PrepareUserCommand(const Event& event);
		Event&	PrepareJoinCommand(const Event& event);
		Event&	PrepareInviteCommand(const Event& event);
		Event&	PrepareKickCommand(const Event& event);
		Event&	PrepareTopicCommand(const Event& event);
		Event&	PrepareModeCommand(const Event& event);
		Event&	PreparePrivmsgCommand(const Event& event);

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
