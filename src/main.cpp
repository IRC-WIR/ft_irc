#include "irc_server.h"
#include "event_handler.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
		return 1;
	IrcServer	irc_server;
	try{
		irc_server.set_port_no(argv[1]);
		irc_server.set_password(argv[2]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	StartEventListener	start_event_listener = StartEventListener(irc_server);
	EndEventListener	end_event_listener = EndEventListener(irc_server);

	EventHandler	event_handler(start_event_listener, end_event_listener);

	event_handler.executePoll();

	return 0;
}
