#ifndef MESSAGE_H_
	#define MESSAGE_H_

#include "utils.h"
namespace message
{

enum Command
{
	PASS = 0,
	NICK,
	USER,
	JOIN,
	INVITE,
	KICK,
	TOPIC,
	MODE,
	PRIVMSG,
	QUIT,
	NOT_FOUND
};

enum ParseState
{
	PARSE_DEFAULT = 0,
	PARSE_COMMAND,
	PARSE_PARAM,
	PARSE_ERROR,
	PARSE_EMPTY,
	PARSE_COMPLETE
};

class MessageParser
{
	public:
		MessageParser(const std::string& msg);
		void 	ParsingMessage(const std::string& msg);
		void	ParsingCommand(const std::string& command);
		void	Init(const std::string& msg);
		bool	IsEndOfMessage(const char& ch);

		Command	get_command() const;
		ParseState get_state() const;
		std::vector<std::string> get_params() const;
	private:
		std::string	message_;
		Command	command_;
		ParseState state_;
		std::vector<std::string> command_params_;
		static const std::map<std::string, Command> kCommandMap;
		static std::map<std::string, message::Command> createCommandMap();
};

} // namespace message

#endif