#ifndef EVENT_H_
	#define EVENT_H_

#include <vector>
#include <string>

class Event {
	public:
		Event(int fd, int event_type);
		~Event();
		bool	get_is_listening_socket();
		int	get_fd();
		int	get_event_type();
		std::vector<std::string>	get_command_params();

	private:
		const int	fd_;
		const int	event_type_;
		std::vector<std::string>	command_params_;
};

#endif
