#include "check.h"

Check::Check(IrcServer &irc_server) : irc_server_(irc_server)
{
	(void)irc_server_;
	return ;
}

Check::~Check(){

}

EventListener* Check::accept(int fd)
{
	User* new_user = new User(fd);
	irc_server_.add_user(new_user);
	return new_user;
}

std::map<int, std::string> Check::PassCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::NickCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::UserCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::JoinCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::InviteCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::KickCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::TopicCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::ModeCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Check::PrivmsgCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}