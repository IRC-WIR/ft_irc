#ifndef EVENT_H_
	#define EVENT_H_

#include "message.h"

struct ErrorInfo
{
	bool		is_error;
	std::string	error_msg;
	ErrorInfo() : is_error(false), error_msg("") {}
};

class Event {
	public:
		Event(int fd, int event_type);
		~Event();
		int		get_fd() const;
		int		get_event_type() const;
		message::Command	get_command() const;
		const std::vector<std::string>&	get_command_params() const;
		const std::string& 	get_err_msg() const;
		bool	get_is_err() const;
		void	set_command(message::Command command);
		void	set_command_params(const std::vector<std::string>& commmand_params);
		void	set_user_info(bool is_err, const std::string& msg);
	private:
		const int	fd_;
		const int	event_type_;
		message::Command command_;
		std::vector<std::string>	command_params_;
		ErrorInfo	error_info_;

};

#endif
