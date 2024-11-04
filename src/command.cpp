#include "command.h"

const Command

	Command::kPass("PASS"),
	Command::kNick("NICK"),
	Command::kUser("USER"),
	Command::kJoin("JOIN"),
	Command::kInvite("INVITE"),
	Command::kKick("KICK"),
	Command::kTopic("TOPIC"),
	Command::kMode("MODE"),
	Command::kPrivmsg("PRIVMSG"),
	Command::kQuit("QUIT"),
	Command::kNotFound("")
	;

static std::vector<const Command*> CreateCommandList() {
	std::vector<const Command*> ret;
	ret.push_back(&Command::kPass);
	ret.push_back(&Command::kNick);
	ret.push_back(&Command::kUser);
	ret.push_back(&Command::kJoin);
	ret.push_back(&Command::kInvite);
	ret.push_back(&Command::kKick);
	ret.push_back(&Command::kTopic);
	ret.push_back(&Command::kMode);
	ret.push_back(&Command::kPrivmsg);
	ret.push_back(&Command::kQuit);
	ret.push_back(&Command::kNotFound);
	return ret;
}

const std::vector<const Command*>& Command::kCommandList = CreateCommandList();

Command::Command(const std::string& name) : name_(name) {
}

Command::~Command() {
}

const Command& Command::SearchByName(const std::string& name) {
	for (std::vector<const Command*>::const_iterator it = Command::kCommandList.begin(); it != Command::kCommandList.end(); ++it) {
		if ((*it)->get_name() == name)
			return **it;
	}
	return Command::kNotFound;
}

const std::string& Command::get_name() const {
	return this->name_;
}

bool operator== (const Command& command1, const Command& command2) {
	return (&command1 == &command2);
}

bool operator!= (const Command& command1, const Command& command2) {
	return !(command1 == command2);
}
