#include "message.h"

const std::map<std::string, message::Command> message::MessageParser::kCommandMap = message::MessageParser::createCommandMap();

std::map<std::string, message::Command> message::MessageParser::createCommandMap() {
    std::map<std::string, message::Command> m;
    m.insert(std::make_pair("PASS", message::PASS));
    m.insert(std::make_pair("NICK", message::NICK));
    m.insert(std::make_pair("JOIN", message::JOIN));
    m.insert(std::make_pair("INVITE", message::INVITE));
    m.insert(std::make_pair("KICK", message::KICK));
    m.insert(std::make_pair("TOPIC", message::TOPIC));
    m.insert(std::make_pair("MODE", message::MODE));
    m.insert(std::make_pair("PRVIMSG", message::PRVIMSG));
    m.insert(std::make_pair("USER", message::USER));
    return m;
}

message::MessageParser::MessageParser(const std::string& msg) : message_(msg)
{
	ParsingMessage();
}

void message::MessageParser::ParsingMessage()
{
	std::cout << message_ << std::endl;
	std::cout << "the message in buffer: " << message_ << std::endl;
	Init();
	if (message_.empty())
	{
		state_ = PARSE_EMPTY;
		return;
	}
	std::string last_param;
	std::string command = message_;
	while (state_ != PARSE_COMPLETE)
	{
		switch (state_)
		{
			case PARSE_COMMAND:
				ParsingCommand(command);
				break;
			default:
				last_param = utils::ft_split_after(message_, ":");
				if (last_param != "")
					command = utils::ft_split_before(message_, ":");
				state_ = PARSE_COMMAND;
				break;
		}
		if (state_ == PARSE_ERROR)
			break;
	}
}

void message::MessageParser::ParsingCommand(const std::string& command)
{
	std::stringstream ss(command);
	std::string	str;
	while ( getline(ss, str, ' ') ){
		this->command_params_.push_back(str);
	}
	const std::string command_str = this->command_params_[0];
	this->command_params_.erase(command_params_.begin());
	std::map<std::string, message::Command>::const_iterator it = kCommandMap.find(command_str);

	if (it == kCommandMap.end())
	{
		this->command_ = message::NOT_FOUND;
		state_ = PARSE_ERROR;
		return;
	}
	this->command_ = it->second;
	state_ = PARSE_COMPLETE;
}


void message::MessageParser::Init()
{
	command_params_.clear();
}


bool message::MessageParser::IsEndOfMessage(const char& ch)
{
	if (ch == '\r' || ch == '\n')
		return true;
	return false;
}


// Command message::MessageParser::get_command() const
// {
// 	return command_;
// }