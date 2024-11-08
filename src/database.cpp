#include "database.h"
#include "command.h"
#include "channel.h"
#include "channel_event.h"
#include "mode.h"

Database::Database(const std::string& password):server_password_(password){}
Database::~Database() {
	std::set<Finishable*> ptr_set;

	for (std::vector<EventConfigurator*>::iterator it = this->check_element_.begin();
			it != this->check_element_.end(); ++it) {
		ptr_set.insert(*it);
	}
	for (std::vector<EventListener*>::iterator it = this->execute_element_.begin();
			it != this->execute_element_.end(); ++it) {
		ptr_set.insert(*it);
	}
	for (std::set<Finishable*>::iterator it = ptr_set.begin(); it != ptr_set.end(); ++it)
		delete *it;
}

void Database::CreateUser(int fd) {
	User* user = new User(fd);
	check_element_.push_back(user);
	execute_element_.push_back(user);
}

const Channel& Database::CreateChannel(const User& op, const std::string& name) {
	Channel* channel = new Channel(op, name);
	this->check_element_.push_back(channel);
	this->execute_element_.push_back(channel);
	return *channel;
}

void Database::CheckEvent(Event*& event) const {
	Database::CheckCommandAndParams(*event);
	std::size_t vector_length = check_element_.size();
	for (std::size_t i = 0; i < vector_length; i++)
		check_element_[i] -> CheckCommand(event);
	if (event->HasErrorOccurred())
			return ;
	this->AfterCheck(*event);
}

std::map<int, std::string>	Database::ExecuteEvent(const Event& event) {
	std::map<int, std::string> ret;
	for (size_t i = 0; i < execute_element_.size(); i++) {
		OptionalMessage message = execute_element_[i] -> ExecuteCommand(event);
		if (!message.IsEmpty())
			ret.insert(message.MakePair());
	}
	return ret;
}

const std::string& Database::get_server_password() const {
	return server_password_;
}


void Database::DeleteFinishedElements() {
	std::set<Finishable*> ptr_set;

	Database::EraseAndAdd(check_element_, ptr_set);
	Database::EraseAndAdd(execute_element_, ptr_set);
	for (std::set<Finishable*>::iterator it = ptr_set.begin(); it != ptr_set.end(); ++it) {
		const Channel* channel_ptr = dynamic_cast<const Channel*>(*it);
		if (channel_ptr != NULL) {
			for (std::vector<EventListener*>::iterator it2 = this->execute_element_.begin();
					it2 != this->execute_element_.end(); ++it2) {
				User* target = dynamic_cast<User*>(*it2);
				if (target != NULL)
					target->DeleteChannelFromList(*channel_ptr);
			}
		}
		delete *it;
	}
}

void Database::CheckCommandAndParams(Event& event) const {
	const Command& command = event.get_command();

	if (command == Command::kPass)
		CkPassCommand(event);
	else if (command == Command::kNick)
		CkNickCommand(event);
	else if (command == Command::kUser)
		CkUserCommand(event);
	else if (command == Command::kJoin)
		CkJoinCommand(event);
	else if (command == Command::kInvite)
		CkInviteCommand(event);
	else if (command == Command::kKick)
		CkKickCommand(event);
	else if (command == Command::kTopic)
		CkTopicCommand(event);
	else if (command == Command::kMode)
		CkModeCommand(event);
	else if (command == Command::kPrivmsg)
		CkPrivmsgCommand(event);
	else if (command == Command::kQuit)
		CkQuitCommand(event);

}

static bool CheckNoSuchChannel(const Event& event) {
	if (event.get_command() == Command::kInvite
			&& event.get_command_params().size() >= 2)
		return !event.IsChannelEvent();
	else if (event.get_command() == Command::kPrivmsg
			&& event.get_command_params()[0][0] == '#')
		return !event.IsChannelEvent();
	else if (event.get_command() == Command::kMode)
		return !event.IsChannelEvent();
	else if (event.get_command() == Command::kTopic)
		return !event.IsChannelEvent();
	else if (event.get_command() == Command::kKick)
		return !event.IsChannelEvent();
	return false;
}

static bool CheckNoSuchNick(const Event& event) {
	if (event.get_command() == Command::kInvite
			&& event.get_command_params().size() >= 2)
		return (event.get_user_count() == 0);
	else if (event.get_command() == Command::kPrivmsg
			&& event.get_command_params()[0][0] != '#')
		return (event.get_user_count() == 0);
	else if (event.get_command() == Command::kMode) {
		const std::vector<std::string>& params = event.get_command_params();
		if (params.size() >= 3) {
			const Mode mode = Mode::Analyze(params[1]);
			if (mode.get_mode() == 'o')
				return (event.get_user_count() == 0);
		}
	}
	return false;
}

void Database::AfterCheck(Event& event) const {
	// ERR_NOSUCHCHANNEL
	if (CheckNoSuchChannel(event)) {
		event.set_error_status(ErrorStatus::ERR_NOSUCHCHANNEL);
		return ;
	}
	// ERR_NOSUCHNICK
	if (CheckNoSuchNick(event)) {
		event.set_error_status(ErrorStatus::ERR_NOSUCHNICK);
		return ;
	}
	if (event.get_command() == Command::kJoin) {
		if (event.IsChannelEvent()) {
			const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
			if (channel.IsMode('i')
					&& !channel.ContainsUser(event.get_executer())
					&& !event.get_executer().IsInvitedChannel(channel)) {
				event.set_error_status(ErrorStatus::ERR_INVITEONLYCHAN);
				return ;
			}
		}
	}
}

//Check
void Database::CkPassCommand(Event& event) const {
	const int kParamsSize = 1;

	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() < kParamsSize) {
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
		return;
	}
	if (params[0] != get_server_password()) {
		event.set_error_status(ErrorStatus::ERR_PASSWDMISMATCH);
		return;
	}
}

void Database::CkNickCommand(Event& event) const {
	const int kParamsSize = 1;
	if (event.get_command_params().size() < kParamsSize) {
		event.set_error_status(ErrorStatus::ERR_NONICKNAMEGIVEN);
		return ;
	}
	const std::string& new_nickname = event.get_command_params()[0];
	if (new_nickname.length() > 9) {
		event.set_error_status(ErrorStatus::ERR_ERRONEUSNICKNAME);
		return ;
	}
	const std::string must_not_contain = " ,*?!@.";
	for (int i = 0; i < (int)must_not_contain.length(); i++) {
		if (new_nickname.find(must_not_contain[i]) != std::string::npos) {
			event.set_error_status(ErrorStatus::ERR_ERRONEUSNICKNAME);
			return;
		}
	}
	const std::string must_not_start_with = "$:&#~%+";
	if (must_not_start_with.find(new_nickname[0]) != std::string::npos) {
		event.set_error_status(ErrorStatus::ERR_ERRONEUSNICKNAME);
		return ;
	}
	return;
}

void Database::CkUserCommand(Event& event) const {
	const int kParamsSize = 4;

	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() < kParamsSize || params[kParamsSize - 1].empty())
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
}

void Database::CkJoinCommand(Event& event) const {
	const int kParamsSize = 1;
	const int kNameMaxLength = 50;
	const char kStartChar = '#';
	const std::string kMustNotContain(" \7,:"); // \7 == Ctrl+G

	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() < kParamsSize) {
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
		return ;
	}
	const std::string& channel_name = params[0];
	if (channel_name.empty() || channel_name[0] != kStartChar || channel_name.length() > kNameMaxLength) {
		event.set_error_status(ErrorStatus::ERR_NOSUCHCHANNEL);
		return ;
	}
	for (std::string::size_type i = 0; i < kMustNotContain.length(); i++) {
		if (channel_name.find(kMustNotContain[i]) != std::string::npos) {
			event.set_error_status(ErrorStatus::ERR_NOSUCHCHANNEL);
			return ;
		}
	}
}

void Database::CkInviteCommand(Event& event) const {
	(void) event;
	return ;
}

void Database::CkKickCommand(Event& event) const {
	const int kParamsSize = 2;
	if (event.get_command_params().size() < kParamsSize)
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
}

void Database::CkTopicCommand(Event& event) const {
	const int kParamsSize = 1;

	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() < kParamsSize) {
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
		return ;
	}
}

void Database::CkPrivmsgCommand(Event& event) const {
	const std::vector<std::string> &params = event.get_command_params();

	if (params.size() <  2) {
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
		return;
	}
	if (params[1].empty()) {
		event.set_error_status(ErrorStatus::ERR_NOTEXTTOSEND);
		return;
	}
}

void Database::CkModeCommand(Event& event) const {
	const std::string kKeyMustNotContain = ": ";

	const std::vector<std::string>& params = event.get_command_params();
	switch (params.size()) {
	case 0:
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
		return ;
	case 1:
		return ;
	default:
		const Mode mode = Mode::Analyze(params[1]);
		if (mode.get_mode() == '\0') {
			event.set_do_nothing(true);
			return ;
		}
		if (Channel::kHandlingModes.find(mode.get_mode()) == std::string::npos) {
			event.set_error_status(ErrorStatus::ERR_UNKNOWNMODE);
			return ;
		}
		if (mode.get_mode() == 'k' || mode.get_mode() == 'o'
				|| (mode.is_plus() && mode.get_mode() == 'l')) {
			if (params.size() < 3) {
				event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
				return ;
			}
			if (params[2].empty()) {
				event.set_error_status(ErrorStatus::ERR_WRONGMODEPARAMS);
				return ;
			}
			if (mode.is_plus() && mode.get_mode() == 'k') {
				const std::string& key = params[2];
				for (std::string::size_type j = 0; j < kKeyMustNotContain.length(); j++) {
					if (key.find(kKeyMustNotContain[j]) != std::string::npos) {
						event.set_error_status(ErrorStatus::ERR_WRONGMODEPARAMS);
						return ;
					}
				}
			}
			if (mode.get_mode() == 'l') {
				int limit = utils::Stoi(params[2]);
				if (limit < 0) {
					event.set_error_status(ErrorStatus::ERR_WRONGMODEPARAMS);
					return ;
				}
			}
		}
		return ;
	}
}

void Database::CkQuitCommand(Event& event) const {
	(void)event;
}
//check
