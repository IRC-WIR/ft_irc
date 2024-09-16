#include "message.h"

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
	while (state_ != PARSE_COMPLETE)
	{
		switch (state_)
		{
			case PARSE_COMMAND:
				switch(command_)



				default:
					break;

				break;
			default:
				last_param = utils::ft_split_after(message_, ":");
				if (last_param == "")
					state_ = PARSE_COMMAND;
				break;

		}
	}

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