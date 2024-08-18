#include "event.h"

Event::Event(int fd, int event_type) : fd_(fd), event_type_(event_type)
{
	return ;
}

Event::~Event()
{
	return ;
}
