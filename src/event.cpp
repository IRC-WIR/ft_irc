#include "event.h"

Event::Event(int fd, int event_type) : fd_(fd), event_type_(event_type), start_listener_result_(DEFAULT)
{
	return ;
}

Event::~Event()
{
	return ;
}

int Event::get_fd() const
{
	return fd_;
}

int Event::get_event_type() const
{
	return event_type_;
}

message::Command Event::get_command()
{
	return command_;
}

std::vector<std::string> Event::get_command_params()
{
	return command_params_;
}

void Event::set_command(const message::Command& command)
{
	command_ = command;
}

void Event::set_command_params(const std::vector<std::string>& commmand_params)
{
	for (std::vector<std::string>::const_iterator it = commmand_params.begin();
		it != commmand_params.end(); it ++)
	{
		command_params_.push_back(*it);
	}
}

StartListenerResult	Event::get_start_listener_result(){
	return start_listener_result_;
}

void	Event::set_start_listener_result(const StartListenerResult start_listener_result){
	this->start_listener_result_ = start_listener_result;
}