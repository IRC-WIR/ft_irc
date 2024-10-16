#include "message.h"

namespace message {

const std::map<std::string, Command> MessageParser::kCommandMap = MessageParser::CreateCommandMap();

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

MessageParser::MessageParser(const std::string& msg)
{
	ParsingMessage(msg);
}

void MessageParser::ParsingMessage(const std::string& msg)
{
	Init(msg);
	if (message_.empty())
	{
		state_ = kParseEmpty;
		return;
	}
	std::cout << "message_: " << message_ << std::endl;
	if (!utils::is_ascii_str(message_))
	{
		std::cout << "test in not ascii code" << std::endl;
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
				if (command_params_.empty())
				{
					state_ = kParseEmpty;
					break;
				}
				state_ = kParseComplete;
				break;

			default:
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
		this->command_params_.push_back(str);
	}
	//find command
	const std::string command_str = this->command_params_[0];
	std::map<std::string, Command>::const_iterator it = kCommandMap.find(command_str);
	//can't find command
	if (it == kCommandMap.end())
	{
		this->command_ = kNotFound;
		state_ = kParseError;
		return;
	}

	//find command, remove  commmand string from commad_params vector
	this->command_params_.erase(command_params_.begin());
	this->command_ = it->second;
	state_ = kParseParam;
}


void MessageParser::Init(const std::string& msg)
{
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

bool MessageParser::IsFinishParsing()
{
	return (state_ == kParseError || state_ == kParseEmpty || state_ == kParseComplete);
}

}