#include "irc_server.h"
#include "event_handler.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
		return 1;
	IrcServer	ircServer = IrcSerer(argv[1], argv[2]);
	if (!ircServer)
		return 1;
	
	StartEventListener	startEventListener = StartEventListener(ircServer);
	EndEventListener	endEventListener = EndEventListener(ircServer);
	
	EventHandler	eventHandler(startEventListener, endEventListener);

	eventHandler.executePoll();

	return 0;
}
