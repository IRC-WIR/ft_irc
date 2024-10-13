#ifndef CHANNEL_H_
 # define CHANNEL_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"
#include "user.h"

class Channel: public EventListener, public EventConfigurator{
	public:
		Channel();
		~Channel();

		void CheckCommand(Event& event) const;
		std::pair<int, std::string> ExecuteCommand(const Event& event);
		bool is_finished() const;


	private:
		std::string		topic_;
		std::string		key_;
		std::string		name_;
		int	max_member_num_;
		bool	i_mode;
		bool	t_mode;
		bool	k_mode;
		bool	o_mode;
		bool	l_mode;
		bool	is_delete_;
		std::vector<User*> users_;
		std::vector<User*> operators_;

		std::map<int, std::string> PassCommand(Event& event);
		std::map<int, std::string> NickCommand(Event& event);
		std::map<int, std::string> UserCommand(Event& event);
		std::map<int, std::string> JoinCommand(Event& event);
		std::map<int, std::string> InviteCommand(Event& event);
		std::map<int, std::string> KickCommand(Event& event);
		std::map<int, std::string> TopicCommand(Event& event);
		std::map<int, std::string> ModeCommand(Event& event);
		std::map<int, std::string> PrivmsgCommand(Event& event);
};

#endif
