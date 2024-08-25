#include "user.h"

User::User(){
}

User::User(int fd) : fd_(fd){
}

User::~User(){
}

std::map<int, std::string> User::Pass(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Nick(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Join(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Invite(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Kick(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Topic(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Part(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Prvmsg(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Quit(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}

std::map<int, std::string> User::Mode(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
