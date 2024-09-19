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

std::map<int, std::string> StartEventListener::PassCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::NickCommand(Event event)
{
	(void)event;
	std::cout << "START" << std::endl;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::UserCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::JoinCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::InviteCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::KickCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::TopicCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::PrivmsgCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::ModeCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

