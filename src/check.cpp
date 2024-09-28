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

Event&	Check::PreparePassCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareNickCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareUserCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareJoinCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareInviteCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareKickCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareTopicCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PrepareModeCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::PreparePrivmsgCommand(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}