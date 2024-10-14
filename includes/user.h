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

		std::pair<int, std::string> PassCommand(const Event& event);
		std::pair<int, std::string> NickCommand(const Event& event);
		std::pair<int, std::string> UserCommand(const Event& event);
		std::pair<int, std::string> JoinCommand(const Event& event);
		std::pair<int, std::string> InviteCommand(const Event& event);
		std::pair<int, std::string> KickCommand(const Event& event);
		std::pair<int, std::string> TopicCommand(const Event& event);
		std::pair<int, std::string> ModeCommand(const Event& event);
		std::pair<int, std::string> PrivmsgCommand(const Event& event);
};

#endif
