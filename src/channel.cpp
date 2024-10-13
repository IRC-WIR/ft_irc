#include "channel.h"

Channel::Channel() : is_delete_(false){
		(void)max_member_num_;
		(void)i_mode;
		(void)t_mode;
		(void)k_mode;
		(void)o_mode;
		(void)l_mode;
		(void)is_delete_;
}

Channel::~Channel(){

}

void Channel::CheckCommand(Event& event) const
{
	//未実装
	(void)event;
}

std::pair<int, std::string>* Channel::ExecuteCommand(const Event& event)
{
	//未実装
	std::pair<int, std::string>* ret_pair = new std::pair<int, std::string>();
	(void)event;
	return ret_pair;
}

bool Channel::is_finished() const
{
	//未実装
	return true;
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