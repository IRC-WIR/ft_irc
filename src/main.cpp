#include "server.h"
#include "event_handler.h"
#include "database.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 3)
	{
		std::cerr << "Please execute as follows: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	try
	{
		Database			database;
		utils::CheckDigitalStr(argv[1]);
		EventHandler		event_handler(database, utils::Stoi(argv[1]));
		server::IrcServer	irc_server(event_handler);
		irc_server.set_port_no(argv[1]);
		irc_server.set_password(argv[2]);
		irc_server.Run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
