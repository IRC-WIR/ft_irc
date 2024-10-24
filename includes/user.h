#ifndef USER_H_
 #define USER_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"
#include "error_status.h"
#include "optional_message.h"

class Channel;

class User : public EventListener, public EventConfigurator{
	public:
		User(int fd);
		~User();

		void CheckCommand(Event& event) const;
		OptionalMessage ExecuteCommand(const Event& event);
		std::string CreateErrorMessage(const message::Command& cmd, const ErrorStatus& err_status) const;
		bool IsFinished() const;
		bool IsVerified() const;

		void set_server_password(const std::string& password);
		bool get_is_password_authenticated() const;
		int get_fd() const;
		bool get_is_delete() const;

	private:
		User();
		int		fd_;

		bool	is_password_authenticated_;
		std::string	nick_name_;
		std::string	user_name_;
		std::string	real_name_;
		std::string server_password_;
		std::vector<Channel>	channels_;
		bool is_delete_;

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
