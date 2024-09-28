#ifndef EVENT_CONFIGURATOR_H_
 #define EVENT_CONFIGURATOR_H_


#include "event_listener.h"

class EventConfigurator
{
	public:
		EventConfigurator();
		virtual ~EventConfigurator();
		virtual Event&	PreparePassCommand(const Event& event) = 0;
		virtual Event&	PrepareNickCommand(const Event& event) = 0;
		virtual Event&	PrepareUserCommand(const Event& event) = 0;
		virtual Event&	PrepareJoinCommand(const Event& event) = 0;
		virtual Event&	PrepareInviteCommand(const Event& event) = 0;
		virtual Event&	PrepareKickCommand(const Event& event) = 0;
		virtual Event&	PrepareTopicCommand(const Event& event) = 0;
		virtual Event&	PrepareModeCommand(const Event& event) = 0;
		virtual Event&	PreparePrivmsgCommand(const Event& event) = 0;

	private:

};

#endif
