#include "event_configurator.h"

EventConfigurator::EventConfigurator()
{
	return ;
}

EventConfigurator::~EventConfigurator()
{
	return ;
}

Event&	EventConfigurator::configurate(const Event& event)
{
	switch (event.get_command()){
		case message::PASS:
			return ConfiguratePass(event);
		case message::NICK:
			return ConfigurateNick(event);
		case message::USER:
			return ConfigurateUser(event);
		case message::JOIN:
			return ConfigurateJoin(event);
		case message::INVITE:
			return ConfigurateInvite(event);
		case message::KICK:
			return ConfigurateKick(event);
		case message::TOPIC:
			return ConfigurateTopic(event);
		case message::MODE:
			return ConfigurateMode(event);
		case message::PRIVMSG:
			return ConfiguratePrivmsg(event);
		default:
			return (Event &)event;
	}
}