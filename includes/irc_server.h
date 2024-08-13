#ifndef IRC_SERVER_H_
 #define IRC_SERVER_H_

#include "Event_handler.h"
#include "user.h"
#include "channel.h"
#include "start_event_listener.h"
#include "end_event_listener.h"

class IrcServer{
	public:
		IrcServer();
		IrcServer(std::string port, std::string password);
		~IrcServer();

		std::string	get_password();
		std::vector<Channel>	get_channels();
		std::vector<User>	get_users();
		void	add_channel(Channel channel);
		void	remove_channel(std::string name);
		void	add_user(User user);
		void	remove_channel(std::string nickname);

		bool	ValidPort(std::string port);
		bool	ValidPassword(std::string password);
	private:
		std::vector<User>	users_;
		std::vector<Channel>	channels_;
		StartEventListener*	start_event_listener_;
		EndEventListener*	end_event_listener_;
		EventHandler	event_handler_;
		std::string	password_;
		std::string	port_no_;
};

#endif
