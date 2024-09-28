#ifndef EVENT_CONFIGURATOR_H_
 #define EVENT_CONFIGURATOR_H_


#include "event_listener.h"

class EventConfigurator
{
	public:
		EventConfigurator();
		virtual ~EventConfigurator();
		Event&	configurate(const Event& event);
		virtual Event&	ConfiguratePass(const Event& event) = 0;
		virtual Event&	ConfigurateNick(const Event& event) = 0;
		virtual Event&	ConfigurateUser(const Event& event) = 0;
		virtual Event&	ConfigurateJoin(const Event& event) = 0;
		virtual Event&	ConfigurateInvite(const Event& event) = 0;
		virtual Event&	ConfigurateKick(const Event& event) = 0;
		virtual Event&	ConfigurateTopic(const Event& event) = 0;
		virtual Event&	ConfigurateMode(const Event& event) = 0;
		virtual Event&	ConfiguratePrivmsg(const Event& event) = 0;

	private:

};

#endif
