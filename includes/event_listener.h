#ifndef EVENT_LISTENER_H_
 #define EVENT_LISTENER_H_


#include "event.h"
#include "utils.h"

class EventListener
{
	public:
		EventListener();
		virtual ~EventListener();
		virtual std::map<int, std::string> PassCommand(const Event& event) = 0;
		virtual std::map<int, std::string> NickCommand(const Event& event) = 0;
		virtual std::map<int, std::string> UserCommand(const Event& event) = 0;
		virtual std::map<int, std::string> JoinCommand(const Event& event) = 0;
		virtual std::map<int, std::string> InviteCommand(const Event& event) = 0;
		virtual std::map<int, std::string> KickCommand(const Event& event) = 0;
		virtual std::map<int, std::string> TopicCommand(const Event& event) = 0;
		virtual std::map<int, std::string> ModeCommand(const Event& event) = 0;
		virtual std::map<int, std::string> PrivmsgCommand(const Event& event) = 0;

	private:

};

#endif
