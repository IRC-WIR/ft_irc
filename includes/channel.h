#ifndef CHANNEL_H_
# define CHANNEL_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"
#include "user.h"
#include "optional_message.h"

class Channel: public EventListener, public EventConfigurator{
	public:
		Channel();
		~Channel();

		void CheckCommand(Event& event) const;
		OptionalMessage ExecuteCommand(const Event& event);
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
		OptionalMessage ExPassCommand(const Event& event);
		OptionalMessage ExNickCommand(const Event& event);
		OptionalMessage ExUserCommand(const Event& event);
		OptionalMessage ExJoinCommand(const Event& event);
		OptionalMessage ExInviteCommand(const Event& event);
		OptionalMessage ExKickCommand(const Event& event);
		OptionalMessage ExTopicCommand(const Event& event);
		OptionalMessage ExModeCommand(const Event& event);
		OptionalMessage ExPrivmsgCommand(const Event& event);
};

#endif
