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
	if (!utils::IsAsciiStr(message_))
	{
		command_ = kNotFound;
		state_ = kParseNotAscii;
		return;
	}
	std::string last_param = "";
	std::string command = message_;
	const std::string kDelim = ":";
	std::string::size_type delim_pos = message_.find(kDelim);
	bool has_delim = (delim_pos != std::string::npos);

	if (has_delim) {
		last_param = message_.substr(delim_pos + kDelim.length());
		utils::EraseNewline(last_param);
		command = message_.substr(0, delim_pos);
	}
	state_ = kParseCommand;
	while (!IsFinishParsing())
	{
		switch (state_)
		{
			case kParseCommand:
				ParsingCommand(command);
				break;

			case kParseParam:
				if (has_delim)
					command_params_.push_back(last_param);
				state_ = kParseComplete;
				break;

			default:
				return;
		}
	}
}

void MessageParser::ParsingCommand(const std::string& command)
{
	std::stringstream ss(command);
	std::string	str;
	while ( getline(ss, str, ' ') ) {
		utils::EraseNewline(str);
		if (!str.empty())
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
	utils::ConvertToUpper(command_str);
	std::map<std::string, Command>::const_iterator it = kCommandMap.find(command_str);
	//can't find command
	if (it == kCommandMap.end())
	{
		command_ = kNotFound;
		state_ = kParseError;
		return;
	}
	//find command, remove command string from command_params vector
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