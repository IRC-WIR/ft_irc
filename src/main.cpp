#include "server.h"
#include "event_handler.h"
#include "data_base.h"
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
		DataBase			data_base;
		utils::check_digital_str(argv[1]);
		EventHandler		event_handler(data_base, argv[1]);
		Server::IrcServer	irc_server(event_handler);
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
