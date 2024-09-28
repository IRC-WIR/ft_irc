#ifndef CHANNEL_H_
 # define CHANNEL_H_

#include "event_configurator.h"

class User;

class Channel: public EventConfigurator{
	public:
		Channel();
		~Channel();
		Event&	ConfiguratePass(const Event& event);
		Event&	ConfigurateNick(const Event& event);
		Event&	ConfigurateUser(const Event& event);
		Event&	ConfigurateJoin(const Event& event);
		Event&	ConfigurateInvite(const Event& event);
		Event&	ConfigurateKick(const Event& event);
		Event&	ConfigurateTopic(const Event& event);
		Event&	ConfigurateMode(const Event& event);
		Event&	ConfiguratePrivmsg(const Event& event);

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
