#ifndef MESSAGE_H_
	#define MESSAGE_H_

#include "utils.h"

namespace message
{

enum Command
{
	kCommandDefault = 0,
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
};

enum ParseState
{
	kParseDefault = 0,
	kParseCommand,
	kParseParam,
	kParseError,
	kParseEmpty,
	kParseNotAscii,
	kParseComplete
};

class MessageParser
{
	public:
		MessageParser(const std::string& msg);

		Command	get_command() const;
		ParseState get_state() const;
		std::vector<std::string> get_params() const;
		static const std::map<Command, std::string>& get_command_str_map();

	private:
		std::string	message_;
		Command	command_;
		ParseState state_;
		std::vector<std::string> command_params_;
		static const std::map<std::string, Command> kCommandMap;
		static std::map<std::string, Command> CreateCommandMap();
		static const std::map<Command, std::string> kCommandStrMap;
		static std::map<Command, std::string> CreateCommandStrMap();

		bool	IsFinishParsing();
		void	ParsingMessage(const std::string& msg);
		void	ParsingCommand(const std::string& command);
		void	Init(const std::string& msg);
		bool	IsEndOfMessage(const char& ch);
};

} // namespace message

#endif