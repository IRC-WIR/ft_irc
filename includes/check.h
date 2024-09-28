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
		Event&	PreparePassCommand(const Event& event);
		Event&	PrepareNickCommand(const Event& event);
		Event&	PrepareUserCommand(const Event& event);
		Event&	PrepareJoinCommand(const Event& event);
		Event&	PrepareInviteCommand(const Event& event);
		Event&	PrepareKickCommand(const Event& event);
		Event&	PrepareTopicCommand(const Event& event);
		Event&	PrepareModeCommand(const Event& event);
		Event&	PreparePrivmsgCommand(const Event& event);

	private:
		IrcServer& irc_server_;
};

#endif
