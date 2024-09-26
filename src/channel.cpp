#include "channel.h"
#include "user.h"

Channel::Channel() {
		(void)max_member_num_;
		(void)i_mode;
		(void)t_mode;
		(void)k_mode;
		(void)o_mode;
		(void)l_mode;
}

Channel::~Channel(){

}

std::map<int, std::string> Channel::PassCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::NickCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::UserCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::JoinCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::InviteCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::KickCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::TopicCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::ModeCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}
std::map<int, std::string> Channel::PrivmsgCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	return error_message;
}