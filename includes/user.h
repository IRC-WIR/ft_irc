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
		void set_server_password(const std::string& password);
		bool get_is_password_authenticated() const;
		int get_fd() const;

	private:
		std::map<int, std::string> PassCommand(Event& event);
		std::map<int, std::string> NickCommand(Event& event);
		std::map<int, std::string> UserCommand(Event& event);
		std::map<int, std::string> JoinCommand(Event& event);
		std::map<int, std::string> InviteCommand(Event& event);
		std::map<int, std::string> KickCommand(Event& event);
		std::map<int, std::string> TopicCommand(Event& event);
		std::map<int, std::string> ModeCommand(Event& event);
		std::map<int, std::string> PrivmsgCommand(Event& event);

		int	fd_;
		bool	is_password_authenticated_;
		std::string	nick_name_;
		std::string	user_name_;
		std::string server_password_;
		std::vector<Channel>	channels_;
};

#endif
