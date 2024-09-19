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

std::map<int, std::string> EndEventListener::PassCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::NickCommand(Event event)
{
	(void)event;
	std::cout << "END" << std::endl;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::UserCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::JoinCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::InviteCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::KickCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::TopicCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::ModeCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> EndEventListener::PrivmsgCommand(Event event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
