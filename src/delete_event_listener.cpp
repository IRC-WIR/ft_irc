#include "delete_event_listener.h"

DeleteEventListener::DeleteEventListener(IrcServer &irc_server) : irc_server_(irc_server)
{
	(void)irc_server_;
	return ;
}

DeleteEventListener::~DeleteEventListener()
{
	return ;
}

std::map<int, std::string> DeleteEventListener::PassCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::NickCommand(const Event& event)
{
	(void)event;
	std::cout << "END" << std::endl;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::UserCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::JoinCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::InviteCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::KickCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::TopicCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::ModeCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> DeleteEventListener::PrivmsgCommand(const Event& event)
{
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
