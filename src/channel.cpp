#include "channel.h"
#include "user.h"

Channel::Channel(){
		(void)max_member_num_;
		(void)i_mode;
		(void)t_mode;
		(void)k_mode;
		(void)o_mode;
		(void)l_mode;
}

Channel::~Channel(){

}

Event&	Channel::PreparePassCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareNickCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareUserCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareJoinCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareInviteCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareKickCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareTopicCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PrepareModeCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::PreparePrivmsgCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}