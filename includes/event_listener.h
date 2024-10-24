#ifndef EVENT_LISTENER_H_
# define EVENT_LISTENER_H_

# include "finishable.h"
# include "event.h"
# include "optional_message.h"

class EventListener : virtual public Finishable {
	public:
		EventListener() {}
		virtual ~EventListener() {}
		virtual OptionalMessage ExecuteCommand(const Event& event) = 0;
};

#endif
