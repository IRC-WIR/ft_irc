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
		case message::kPass:
			CkPassCommand(event);
			break;
		case message::kNick:
			CkNickCommand(event);
			break;
		case message::kUser:
			CkUserCommand(event);
			break;
		case message::kJoin:
			CkJoinCommand(event);
			break;
		case message::kInvite:
			CkInviteCommand(event);
			break;
		case message::kKick:
			CkKickCommand(event);
			break;
		case message::kTopic:
			CkTopicCommand(event);
			break;
		case message::kMode:
			CkModeCommand(event);
			break;
		case message::kPrivmsg:
			CkPrivmsgCommand(event);
			break;
		default:
			return;
	}
}

OptionalMessage Channel::ExecuteCommand(const Event& event)
{
	switch (event.get_command()) {
		case message::kPass:
			return ExPassCommand(event);
		case message::kNick:
			return ExNickCommand(event);
		case message::kUser:
			return ExUserCommand(event);
		case message::kJoin:
			return ExJoinCommand(event);
		case message::kInvite:
			return ExInviteCommand(event);
		case message::kKick:
			return ExKickCommand(event);
		case message::kTopic:
			return ExTopicCommand(event);
		case message::kMode:
			return ExModeCommand(event);
		case message::kPrivmsg:
			return ExPrivmsgCommand(event);
		default:
			return OptionalMessage::Empty();
	}
}

bool Channel::IsFinished() const
{
	//未実装
	return false;
}

//Execute
OptionalMessage Channel::ExPassCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExNickCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExUserCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExJoinCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExInviteCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExKickCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExTopicCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExModeCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExPrivmsgCommand(const Event& event){
	(void)event;
	return OptionalMessage::Empty();
}
//Execute


//Check
void Channel::CkPassCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkNickCommand(Event& event) const
{
	(void)event;
	return ;
}

void Channel::CkUserCommand(Event& event) const
{
	(void)event;
	std::cout << "Check User called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkJoinCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Join called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkInviteCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vite called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkKickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkTopicCommand(Event& event) const
{
	(void)event;
	std::cout << "Check opic called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkPrivmsgCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vmsg called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkModeCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}
//check