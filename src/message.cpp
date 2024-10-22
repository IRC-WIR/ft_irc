#include "message.h"

namespace message {

const std::map<std::string, Command> MessageParser::kCommandMap = MessageParser::CreateCommandMap();
const std::map<Command, std::string> MessageParser::kCommandStrMap = MessageParser::CreateCommandStrMap();

//here
//convert to Upper & compare from map
std::map<std::string, Command> MessageParser::CreateCommandMap() {
    std::map<std::string, Command> m;
    m.insert(std::make_pair("PASS", kPass));
    m.insert(std::make_pair("NICK", kNick));
    m.insert(std::make_pair("USER", kUser));
    m.insert(std::make_pair("JOIN", kJoin));
    m.insert(std::make_pair("INVITE", kInvite));
    m.insert(std::make_pair("KICK", kKick));
    m.insert(std::make_pair("TOPIC", kTopic));
    m.insert(std::make_pair("MODE", kMode));
    m.insert(std::make_pair("PRIVMSG", kPrivmsg));
    m.insert(std::make_pair("QUIT", kQuit));
    return m;
}

std::map<Command, std::string> MessageParser::CreateCommandStrMap() {
	std::map<Command, std::string> m;
	m.insert(std::make_pair(kPass, "PASS"));
	m.insert(std::make_pair(kNick, "NICK"));
	m.insert(std::make_pair(kUser, "USER"));
	m.insert(std::make_pair(kJoin, "JOIN"));
	m.insert(std::make_pair(kInvite, "INVITE"));
	m.insert(std::make_pair(kKick, "KICK"));
	m.insert(std::make_pair(kTopic, "TOPIC"));
	m.insert(std::make_pair(kMode, "MODE"));
	m.insert(std::make_pair(kPrivmsg, "PRIVMSG"));
	m.insert(std::make_pair(kQuit, "QUIT"));
	return m;
}

MessageParser::MessageParser(const std::string& msg)
{
	ParsingMessage(msg);
}

void MessageParser::ParsingMessage(const std::string& msg)
{
	Init(msg);
	if (!utils::is_ascii_str(message_))
	{
		command_ = kNotFound;
		state_ = KParseNotAscii;
		return;
	}
	std::string last_param;
	std::string command = message_;
	while (!IsFinishParsing())
	{
		switch (state_)
		{
			case kParseCommand:
				ParsingCommand(command);
				break;

			case kParseParam:
				if (!last_param.empty())
					command_params_.push_back(last_param);
				state_ = kParseComplete;
				break;

			default:
			//debug in parsing
				std::cout << "message_:" << message_ << std::endl;
				last_param = utils::ft_split_after(message_, ":");
				if (!last_param.empty())
				{
					utils::erase_newline(last_param);
					command = utils::ft_split_before(message_, ":");
				}
				state_ = kParseCommand;
				break;
		}
	}
}

void MessageParser::ParsingCommand(const std::string& command)
{
	std::stringstream ss(command);
	std::string	str;
	while ( getline(ss, str, ' ') ){
		utils::erase_newline(str);
		if (str.empty())
			continue;
		command_params_.push_back(str);
	}
	//input like "/r/n"
	if (command_params_.size() == 0)
	{
		command_ = kNotFound;
		state_ = kParseEmpty;
		return;
	}
	//find command
	std::string command_str = command_params_[0];
	utils::convert_to_upper(command_str);
	std::map<std::string, Command>::const_iterator it = kCommandMap.find(command_str);
	//can't find command
	if (it == kCommandMap.end())
	{
		command_ = kNotFound;
		state_ = kParseError;
		return;
	}
	//find command, remove commmand string from commad_params vector
	command_params_.erase(command_params_.begin());
	command_ = it->second;
	state_ = kParseParam;
}


void MessageParser::Init(const std::string& msg)
{
	command_ = kCommandDefault;
	state_ = kParseDefault;
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

const std::map<Command, std::string>& MessageParser::get_command_str_map()
{
	return message::MessageParser::kCommandStrMap;
}


bool MessageParser::IsFinishParsing()
{
	return (state_ == kParseError || state_ == kParseEmpty || state_ == kParseComplete);
}

}