#ifndef EVENT_LISTENER_H_
 #define EVENT_LISTENER_H_


#include "event.h"
#include "utils.h"

class EventListener
{
	public:
		EventListener();
		virtual ~EventListener();
		virtual std::pair<int, std::string>	ExecuteCommand(const Event& event) = 0;

	private:

};

#endif
