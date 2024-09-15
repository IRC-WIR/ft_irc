#ifndef EVENT_LISTENER_H_
 #define EVENT_LISTENER_H_

#include <map>
#include <iostream>
#include "event.h"

class EventListener
{
	public:
		EventListener();
		virtual ~EventListener();
		virtual std::map<int, std::string> Pass(Event event) = 0;
		virtual std::map<int, std::string> Nick(Event event) = 0;
		virtual std::map<int, std::string> User(Event event) = 0;
		virtual std::map<int, std::string> Join(Event event) = 0;
		virtual std::map<int, std::string> Invite(Event event) = 0;
		virtual std::map<int, std::string> Kick(Event event) = 0;
		virtual std::map<int, std::string> Topic(Event event) = 0;
		virtual std::map<int, std::string> Mode(Event event) = 0;
		virtual std::map<int, std::string> Prvmsg(Event event) = 0;

	private:

};

#endif
