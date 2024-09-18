#ifndef EVENT_H_
	#define EVENT_H_

#include "utils.h"
#include "message.h"

class Event {
	public:
		Event(int fd, int event_type);
		~Event();
		int		get_fd() const;
		int		get_event_type() const;
		message::Command	get_command();
		std::vector<std::string>	get_command_params();
		void	set_command(const message::Command& command);
		void	set_command_params(const std::vector<std::string>& commmand_params);

	private:
		const int	fd_;
		const int	event_type_;
		message::Command command_;
		std::vector<std::string>	command_params_;
};

#endif
