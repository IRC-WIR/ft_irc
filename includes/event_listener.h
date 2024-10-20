#ifndef EVENT_LISTENER_H_
# define EVENT_LISTENER_H_

# include "finishable.h"
# include "event.h"

class EventListener : virtual public Finishable {
	public:
		EventListener() {}
		virtual ~EventListener() {}
		virtual std::pair<int, std::string> ExecuteCommand(const Event& event) = 0;
};

#endif
