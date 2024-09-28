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

Event&	Channel::ConfiguratePass(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateNick(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateUser(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateJoin(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateInvite(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateKick(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateTopic(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfigurateMode(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Channel::ConfiguratePrivmsg(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}