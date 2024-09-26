#include "event_listener.h"

EventListener::EventListener()
{
	return ;
}

EventListener::~EventListener()
{
	return ;
}

void EventListener::ExecuteCommand(std::map<int, std::string>& response, Event& event)
{
	switch (event.get_command())
	{
		case message::PASS:
			utils::mergeMaps(response, PassCommand(event));
			break;
		case message::NICK:
			utils::mergeMaps(response, NickCommand(event));
			break;
		case message::USER:
			utils::mergeMaps(response, UserCommand(event));
			break;
		case message::JOIN:
			utils::mergeMaps(response, JoinCommand(event));
			break;
		case message::INVITE:
			utils::mergeMaps(response, InviteCommand(event));
			break;
		case message::KICK:
			utils::mergeMaps(response, KickCommand(event));
			break;
		case message::TOPIC:
			utils::mergeMaps(response, TopicCommand(event));
			break;
		case message::MODE:
			utils::mergeMaps(response, ModeCommand(event));
			break;
		case message::PRIVMSG:
			utils::mergeMaps(response, PrivmsgCommand(event));
			break;
		default:
			return ;
	}
}