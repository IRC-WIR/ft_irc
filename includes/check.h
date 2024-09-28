#ifndef CHECK_H_
 # define CHECK_H_

#include "event_configurator.h"
#include "irc_server.h"

class IrcServer;

class Check: public EventConfigurator{
	public:
		Check(IrcServer& ircServer);
		~Check();
		EventListener*	accept(int fd);
		Event&	ConfiguratePass(const Event& event);
		Event&	ConfigurateNick(const Event& event);
		Event&	ConfigurateUser(const Event& event);
		Event&	ConfigurateJoin(const Event& event);
		Event&	ConfigurateInvite(const Event& event);
		Event&	ConfigurateKick(const Event& event);
		Event&	ConfigurateTopic(const Event& event);
		Event&	ConfigurateMode(const Event& event);
		Event&	ConfiguratePrivmsg(const Event& event);

	private:
		IrcServer& irc_server_;
};

#endif
