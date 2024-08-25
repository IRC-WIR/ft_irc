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

std::map<int, std::string> StartEventListener::Pass(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Nick(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Join(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Invite(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Kick(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Topic(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Part(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Prvmsg(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Quit(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> StartEventListener::Mode(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

