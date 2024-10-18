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

		//check command
		void CkPassCommand(Event& event) const;
		void CkNickCommand(Event& event) const;
		void CkUserCommand(Event& event) const;
		void CkJoinCommand(Event& event) const;
		void CkInviteCommand(Event& event) const;
		void CkKickCommand(Event& event) const;
		void CkTopicCommand(Event& event) const;
		void CkModeCommand(Event& event) const;
		void CkPrivmsgCommand(Event& event) const;

		//execute command
		std::pair<int, std::string> ExPassCommand(const Event& event);
		std::pair<int, std::string> ExNickCommand(const Event& event);
		std::pair<int, std::string> ExUserCommand(const Event& event);
		std::pair<int, std::string> ExJoinCommand(const Event& event);
		std::pair<int, std::string> ExInviteCommand(const Event& event);
		std::pair<int, std::string> ExKickCommand(const Event& event);
		std::pair<int, std::string> ExTopicCommand(const Event& event);
		std::pair<int, std::string> ExModeCommand(const Event& event);
		std::pair<int, std::string> ExPrivmsgCommand(const Event& event);
};

#endif
