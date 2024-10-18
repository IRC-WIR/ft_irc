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
	switch (event.get_command())
	{
		case message::PASS:
			CkPassCommand(event);
			break;
		case message::NICK:
			CkNickCommand(event);
			break;
		case message::USER:
			CkUserCommand(event);
			break;
		case message::JOIN:
			CkJoinCommand(event);
			break;
		case message::INVITE:
			CkInviteCommand(event);
			break;
		case message::KICK:
			CkKickCommand(event);
			break;
		case message::TOPIC:
			CkTopicCommand(event);
			break;
		case message::MODE:
			CkModeCommand(event);
			break;
		case message::PRIVMSG:
			CkPrivmsgCommand(event);
			break;
		default:
			return;
	}
}

std::pair<int, std::string> Channel::ExecuteCommand(const Event& event)
{
	std::pair<int, std::string> ret_pair;

	switch (event.get_command())
	{
		case message::PASS:
			ret_pair = ExPassCommand(event);
			break;
		case message::NICK:
			ret_pair = ExNickCommand(event);
			break;
		case message::USER:
			ret_pair = ExUserCommand(event);
			break;
		case message::JOIN:
			ret_pair = ExJoinCommand(event);
			break;
		case message::INVITE:
			ret_pair = ExInviteCommand(event);
			break;
		case message::KICK:
			ret_pair = ExKickCommand(event);
			break;
		case message::TOPIC:
			ret_pair = ExTopicCommand(event);
			break;
		case message::MODE:
			ret_pair = ExModeCommand(event);
			break;
		case message::PRIVMSG:
			ret_pair = ExPrivmsgCommand(event);
			break;
		default:
			return ret_pair;
	}
	return ret_pair;
}

bool Channel::is_finished() const
{
	//未実装
	return true;
}

//Execute
std::pair<int, std::string> Channel::ExPassCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExNickCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExUserCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExJoinCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExInviteCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExKickCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExTopicCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExModeCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
std::pair<int, std::string> Channel::ExPrivmsgCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	return ret_pair;
}
//Execute


//Check
void Channel::CkPassCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkNickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkUserCommand(Event& event) const
{
	(void)event;
	std::cout << "Check User called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkJoinCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Join called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkInviteCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vite called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkKickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkTopicCommand(Event& event) const
{
	(void)event;
	std::cout << "Check opic called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkPrivmsgCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vmsg called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void Channel::CkModeCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}
//check