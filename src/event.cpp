#include "event.h"

const std::string Event::NoErrorException::kMessage = "error: there is no ErrorStatus.";

Event::Event(int fd, int event_type)
		: fd_(fd), event_type_(event_type), error_status_(NULL) {
	return ;
}

Event::Event(const Event& src)
		: fd_(src.get_fd()), event_type_(src.get_event_type()), error_status_(src.error_status_) {
	this->set_command(src.get_command());
	this->set_command_params(src.get_command_params());
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

const ErrorStatus& Event::get_error_status() const {
	if (!this->HasErrorOccurred())
		throw Event::NoErrorException();
	return *this->error_status_;
}

void Event::set_command(message::Command command) {
	command_ = command;
}

void Event::set_command_params(const std::vector<std::string>& commmand_params) {
	command_params_.clear();
	for (std::vector<std::string>::const_iterator it = commmand_params.begin();
		it != commmand_params.end(); it ++)
	{
		command_params_.push_back(*it);
	}
}

void Event::set_error_status(const ErrorStatus& error_status) {
	this->error_status_ = &error_status;
}

bool Event::HasErrorOccurred() const {
	return (this->error_status_ != NULL);
}

Event::NoErrorException::NoErrorException()
		: std::runtime_error(Event::NoErrorException::kMessage) {
	return ;
}