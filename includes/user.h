#ifndef USER_H_
 #define USER_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"

class Channel;

class User : public EventListener, public EventConfigurator{
	public:
		User(int fd);
		~User();

		void CheckCommand(Event& event) const;
		std::pair<int, std::string> ExecuteCommand(const Event& event);
		bool is_finished() const;
		bool is_verified() const;

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
