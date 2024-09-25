#ifndef USER_H_
 #define USER_H_

#include "event_listener.h"
#include "utils.h"

class Channel;

class User : public EventListener{
	public:
		User();
		User(int fd);
		~User();
		std::map<int, std::string> PassCommand(const Event& event);
		std::map<int, std::string> NickCommand(const Event& event);
		std::map<int, std::string> UserCommand(const Event& event);
		std::map<int, std::string> JoinCommand(const Event& event);
		std::map<int, std::string> InviteCommand(const Event& event);
		std::map<int, std::string> KickCommand(const Event& event);
		std::map<int, std::string> TopicCommand(const Event& event);
		std::map<int, std::string> ModeCommand(const Event& event);
		std::map<int, std::string> PrivmsgCommand(const Event& event);
		void set_server_password(const std::string& password);
		bool get_is_password_authenticated() const;
		int get_fd() const;

	private:
		int	fd_;
		bool	is_password_authenticated_;
		std::string	nick_name_;
		std::string	user_name_;
		std::string server_password_;
		std::vector<Channel>	channels_;
};

#endif
