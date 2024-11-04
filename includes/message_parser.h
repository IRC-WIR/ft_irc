#ifndef MESSAGE_PARSER_H_
	#define MESSAGE_PARSER_H_

#include "utils.h"
#include "command.h"

class MessageParser {
	public:
		enum ParseState {
			kParseDefault = 0,
			kParseCommand,
			kParseParam,
			kParseError,
			kParseEmpty,
			kParseNotAscii,
			kParseComplete
		};

		MessageParser(const std::string& msg);

		const Command&	get_command(void) const;
		ParseState get_state(void) const;
		std::vector<std::string> get_params(void) const;

	private:
		std::string	message_;
		const Command*	command_;
		ParseState state_;
		std::vector<std::string> command_params_;

		bool	IsFinishParsing();
		void	ParsingMessage(const std::string& msg);
		void	ParsingCommand(const std::string& command);
		void	Init(const std::string& msg);
		bool	IsEndOfMessage(const char& ch);
};

#endif