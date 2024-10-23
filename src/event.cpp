#include "event.h"

Event::Event(int fd, int event_type) : fd_(fd), event_type_(event_type) {
	return ;
}

Event::~Event() {
	return ;
}

int Event::get_fd() const {
	return fd_;
}

int Event::get_event_type() const {
	return event_type_;
}

message::Command Event::get_command() const {
	return command_;
}

const std::vector<std::string>& Event::get_command_params() const {
	return command_params_;
}

const std::string& 	Event::get_err_msg() const {
	return error_info_.error_msg;
}

bool	Event::get_is_err() const {
	return error_info_.is_error;
}

void Event::set_command(message::Command command) {
	command_ = command;
}

void Event::set_command_params(const std::vector<std::string>& commmand_params) {
	for (std::vector<std::string>::const_iterator it = commmand_params.begin();
		it != commmand_params.end(); it ++) {
		command_params_.push_back(*it);
	}
}

void Event::set_user_info(bool is_err, const std::string& msg) {
	error_info_.is_error = is_err;
	error_info_.error_msg = msg;
}