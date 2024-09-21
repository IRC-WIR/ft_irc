#include "start_event_listener.h"

StartEventListener::StartEventListener(IrcServer &irc_server) : irc_server_(irc_server)
{
	(void)irc_server_;
	return ;
}

StartEventListener::~StartEventListener()
{
	return ;
}

EventListener* StartEventListener::accept(int fd)
{
	User* new_user = new User(fd);
	irc_server_.add_user(new_user);
	return new_user;
}

std::map<int, std::string> StartEventListener::PassCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::NickCommand(Event& event)
{
	
	std::map<int, std::string>	message_map;
	//パラメータが与えられない場合
	if (event.get_command_params().size() < 1){
		std::cout << ":No nickname given" << std::endl;
		message_map.insert(std::make_pair(event.get_fd(), ":No nickname given"));
		return message_map;
	}
	std::string new_nickname = event.get_command_params().at(0);
	std::vector<User*> users = this->irc_server_.get_users();
	for (std::vector<User*>::const_iterator it = users.begin(); it != users.end(); it ++)
	{
		if ((*it)->get_nick_name() == new_nickname)
		{
			event.set_start_listener_result(ERR_NICKNAMEINUSE);
			std::cout << new_nickname << " :Nickname is already in use" << std::endl;
			message_map.insert(std::make_pair(event.get_fd(), new_nickname + " :Nickname is already in use"));
		}
	}
	std::cout << "INSIDE START :" << event.get_start_listener_result() << std::endl;
	return message_map;
}

std::map<int, std::string> StartEventListener::UserCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::JoinCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::InviteCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::KickCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::TopicCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::PrivmsgCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::ModeCommand(Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

