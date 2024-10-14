#include "message.h"

namespace message {

const std::map<std::string, Command> MessageParser::kCommandMap = MessageParser::CreateCommandMap();

std::map<std::string, Command> MessageParser::CreateCommandMap() {
    std::map<std::string, Command> m;
    m.insert(std::make_pair("PASS", PASS));
    m.insert(std::make_pair("NICK", NICK));
    m.insert(std::make_pair("JOIN", JOIN));
    m.insert(std::make_pair("INVITE", INVITE));
    m.insert(std::make_pair("KICK", KICK));
    m.insert(std::make_pair("TOPIC", TOPIC));
    m.insert(std::make_pair("MODE", MODE));
    m.insert(std::make_pair("PRIVMSG", PRIVMSG));
    m.insert(std::make_pair("USER", USER));
    return m;
}

MessageParser::MessageParser(const std::string& msg)
{
	ParsingMessage(msg);
}

void MessageParser::ParsingMessage(const std::string& msg)
{
	Init(msg);
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

			case PARSE_PARAM:
				if (!last_param.empty())
					command_params_.push_back(last_param);
				if (command_params_.empty())
				{
					state_ = PARSE_EMPTY;
					break;
				}
				state_ = PARSE_COMPLETE;
				break;

			default:
				last_param = utils::ft_split_after(message_, ":");
				if (!last_param.empty())
				{
					utils::erase_space(last_param);
					command = utils::ft_split_before(message_, ":");
				}
				state_ = PARSE_COMMAND;
				break;
		}
		if (state_ == PARSE_ERROR || state_ == PARSE_EMPTY)
			break;
	}
}

void MessageParser::ParsingCommand(const std::string& command)
{
	std::stringstream ss(command);
	std::string	str;
	while ( getline(ss, str, ' ') ){
		utils::erase_space(str);
		this->command_params_.push_back(str);
	}
	const std::string command_str = this->command_params_[0];
	std::cout << command_str << std::endl;
	this->command_params_.erase(command_params_.begin());

	std::map<std::string, Command>::const_iterator it = kCommandMap.find(command_str);

	if (it == kCommandMap.end())
	{
		this->command_ = NOT_FOUND;
		state_ = PARSE_ERROR;
		return;
	}
	this->command_ = it->second;
	state_ = PARSE_PARAM;
}


void MessageParser::Init(const std::string& msg)
{
	state_ = PARSE_DEFAULT;
	message_ = msg;
	command_params_.clear();
}


bool MessageParser::IsEndOfMessage(const char& ch)
{
	if (ch == '\r' || ch == '\n')
		return true;
	return false;
}


Command MessageParser::get_command() const
{
	return command_;
}

ParseState MessageParser::get_state() const
{
	return state_;
}

std::vector<std::string> MessageParser::get_params() const
{
	return command_params_;
}

}