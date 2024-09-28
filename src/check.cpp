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

Event&	Check::ConfiguratePass(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateNick(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateUser(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateJoin(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateInvite(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateKick(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateTopic(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfigurateMode(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}
Event&	Check::ConfiguratePrivmsg(const Event& event)
{
	(void)event;
	Event* new_event = new Event(0, 0);
	return *new_event;
}