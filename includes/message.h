#ifndef MESSAGE_H_
	#define MESSAGE_H_

#include "utils.h"
namespace message
{

enum Command
{
	PASS,
	NICK,
	JOIN,
	INVITE,
	KICK,
	TOPIC,
	MODE,
	PRVIMSG,
	USER
};

enum ParseState
{
	PARSE_SPACE = 0,
	PARSE_COMMAND,
	PARSE_ERROR,
	PARSE_EMPTY,
	PARSE_COMPLETE
};

class MessageParser
{
	public:
		MessageParser(const std::string& msg);
		void 	ParsingMessage();
		void	Init();
		bool	IsEndOfMessage(const char& ch);
		


		//Command	get_command() const;


	private:
		Command	command_;
		ParseState state_;
		std::string	message_;
		std::vector<std::string> command_params_;
};

} // namespace message

#endif