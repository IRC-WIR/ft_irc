#ifndef USER_H_
 #define USER_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"
#include "error_status.h"
#include "optional_message.h"

class Channel;

class User : public EventListener, public EventConfigurator {
	public:
		User(int fd);
		~User();

		void CheckCommand(Event*& event) const;
		OptionalMessage ExecuteCommand(const Event& event);
		std::string CreateErrorMessage(const message::Command& cmd, const ErrorStatus& err_status) const;
		bool IsFinished(void) const;
		bool IsVerified(void) const;

		void set_is_password_authenticated(bool is_pw_authenticated);
		bool get_is_password_authenticated(void) const;
		void set_displayed_welcome(bool is_verified);
		bool is_displayed_welcome(void) const;

		int get_fd(void) const;
		bool get_is_delete(void) const;
		const std::string& get_nick_name(void) const;
		const std::string& get_user_name(void) const;
		const std::string& get_real_name(void) const;

	private:
		User(void);
		int		fd_;

		bool	is_password_authenticated_;
		std::string	nick_name_;
		std::string	user_name_;
		std::string	real_name_;
		bool is_delete_;
		utils::MyVector<const Channel*> joining_channels_;
		std::string GenerateJoinDetailMessage(const Channel&) const;
		bool is_displayed_welcome_;

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
