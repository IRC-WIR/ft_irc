#ifndef MESSAGE_H_
	#define MESSAGE_H_

#include "utils.h"
namespace message
{

enum ParseState
{
	PARSE_BEFORE = 0,
	PARSE_ERROR
};

class MessageParser
{
	public:
		MessageParser(const std::string& msg);
		void	ParsingMessage();
		bool	IsEndOfMessage(const char& ch);


	private:
		std::string	message_;
		size_t iterator_;
		std::string	command_;
		std::vector<std::string> command_params_;

};

} // namespace message

#endif