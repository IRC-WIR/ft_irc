#ifndef EVENT_CONFIGURATOR_H_
	#define EVENT_CONFIGURATOR_H_

#include "event.h"

class EventConfigurator{

	public:
		EventConfigurator();
		virtual ~EventConfigurator();
		virtual void CheckCommand(Event& event) const = 0;
		virtual bool is_finished() const = 0;

	private:

};

#endif