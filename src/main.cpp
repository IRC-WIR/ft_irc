#include "server.h"
#include "event_handler.h"
#include "database.h"
#include "utils.h"

int	main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Please execute as follows: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	try {
		utils::CheckPort(argv[1]);
		Database			database(argv[2]);
		EventHandler		event_handler(database, utils::Stoi(argv[1]));
		server::IrcServer	irc_server(event_handler);
		irc_server.set_port_no(argv[1]);
		irc_server.set_password(argv[2]);
		irc_server.Run();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::exit(1);
	}

	return 0;
}
