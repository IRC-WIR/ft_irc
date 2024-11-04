#ifndef MESSAGE_H_
	#define MESSAGE_H_

#include "utils.h"

namespace message {

class Command {
	public:
	static const Command
		kPass,
		kNick,
		kUser,
		kJoin,
		kInvite,
		kKick,
		kTopic,
		kMode,
		kPrivmsg,
		kQuit,
		kNotFound
	;

	static const Command& SearchByName(const std::string&);
	const std::string& get_name(void) const;

	private:
		static const std::vector<const Command*>& kCommandList;
		const std::string name_;

		Command(const std::string&);
		~Command();
};

enum ParseState {
	kParseDefault = 0,
	kParseCommand,
	kParseParam,
	kParseError,
	kParseEmpty,
	kParseNotAscii,
	kParseComplete
};

class MessageParser {
	public:
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

bool operator== (const Command&, const Command&);
bool operator!= (const Command&, const Command&);

} // namespace message

#endif