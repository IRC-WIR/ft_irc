#include "end_event_listener.h"

EndEventListener::EndEventListener(IrcServer &irc_server) : irc_server_(irc_server)
{
	(void)irc_server_;
	return ;
}

EndEventListener::~EndEventListener()
{
	return ;
}

std::map<int, std::string> EndEventListener::Pass(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Nick(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Join(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Invite(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Kick(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Topic(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Part(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Privmsg(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Quit(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::Mode(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

