#include "message.h"

message::MessageParser::MessageParser(const std::string& msg) : message_(msg), iterator_(0)
{
	ParsingMessage();
}

void message::MessageParser::ParsingMessage()
{
	std::cout << message_ << std::endl;
	std::cout << "the message in buffer: " << message_ << std::endl;
	while (!IsEndOfMessage(message_[iterator_]))
	{
		if (message_[iterator_] == ' ')
			command_ = message_.substr(0, iterator_ + 1);
		iterator_++;
	}
	std::cout << command_ << std::endl;
}

bool message::MessageParser::IsEndOfMessage(const char& ch)
{
	if (ch == '\r' || ch == '\n')
		return true;
	return false;
}
