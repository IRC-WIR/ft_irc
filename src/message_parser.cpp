#include "message_parser.h"

MessageParser::MessageParser(const std::string& msg) {
	ParsingMessage(msg);
}

void MessageParser::ParsingMessage(const std::string& msg) {
	Init(msg);
	if (!utils::IsAsciiStr(message_)) {
		command_ = &Command::kNotFound;
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
	while (!IsFinishParsing()) {
		switch (state_) {
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

void MessageParser::ParsingCommand(const std::string& input) {
	std::stringstream ss(input);
	std::string	str;
	while ( getline(ss, str, ' ') ) {
		utils::EraseNewline(str);
		if (!str.empty())
			command_params_.push_back(str);
	}
	//input like "/r/n"
	if (command_params_.size() == 0) {
		command_ = &Command::kNotFound;
		state_ = kParseEmpty;
		return;
	}
	//find command
	std::string command_str = command_params_[0];
	utils::ConvertToUpper(command_str);
	const Command& command = Command::SearchByName(command_str);
	//can't find command
	if (command == Command::kNotFound) {
		command_ = &Command::kNotFound;
		state_ = kParseError;
		return;
	}
	//find command, remove command string from command_params vector
	command_params_.erase(command_params_.begin());
	command_ = &command;
	state_ = kParseParam;
}


void MessageParser::Init(const std::string& msg) {
	command_ = &Command::kNotFound;
	state_ = kParseDefault;
	message_ = msg;
	command_params_.clear();
}


bool MessageParser::IsEndOfMessage(const char& ch) {
	if (ch == '\r' || ch == '\n')
		return true;
	return false;
}


const Command& MessageParser::get_command() const {
	return *command_;
}

MessageParser::ParseState MessageParser::get_state() const {
	return state_;
}

std::vector<std::string> MessageParser::get_params() const {
	return command_params_;
}

bool MessageParser::IsFinishParsing() {
	return (state_ == kParseError || state_ == kParseEmpty || state_ == kParseComplete);
}