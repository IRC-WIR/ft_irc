#ifndef EVENT_CONFIGURATOR_H_
# define EVENT_CONFIGURATOR_H_

# include "finishable.h"
# include "event.h"

class EventConfigurator : virtual public Finishable {
	public:
		EventConfigurator() {}
		virtual ~EventConfigurator() {}
		virtual void CheckCommand(Event*& event) const = 0;
};

#endif