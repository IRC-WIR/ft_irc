#include "database.h"
#include "message.h"
#include "channel.h"
#include "channel_event.h"

Database::Database(const std::string& password):server_password_(password){};
Database::~Database(){};

void Database::CreateUser(int fd) {
	try {
		User* user = new User(fd);
		check_element_.push_back(user);
		execute_element_.push_back(user);
	} catch(const std::bad_alloc& e) {
		std::cerr << "bad to alloc memory" << e.what() << std::endl;
	} catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}
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
	this->AfterCheck(*event);
}

std::map<int, std::string>	Database::ExecuteEvent(const Event& event) {
	std::map<int, std::string> ret;
	std::size_t vector_length = execute_element_.size();
	std::cout << "vector_length: " << vector_length << std::endl;
	for (size_t i = 0; i < vector_length; i++) {
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
	for (std::set<Finishable*>::iterator it = ptr_set.begin(); it != ptr_set.end(); ++it)
		delete *it;
}

void Database::CheckCommandAndParams(Event& event) const {
	switch (event.get_command()) {
		case message::kPass:
			CkPassCommand(event);
			break ;
		case message::kNick:
			CkNickCommand(event);
			break ;
		case message::kUser:
			CkUserCommand(event);
			break ;
		case message::kJoin:
			CkJoinCommand(event);
			break ;
		case message::kInvite:
			CkInviteCommand(event);
			break ;
		case message::kKick:
			CkKickCommand(event);
			break ;
		case message::kTopic:
			CkTopicCommand(event);
			break ;
		case message::kMode:
			CkModeCommand(event);
			break ;
		case message::kPrivmsg:
			CkPrivmsgCommand(event);
			break ;
		default:
			break ;
	}
}

static bool IsIgnoringErrorOnJoin(const ErrorStatus& status) {
	return (status == ErrorStatus::ERR_INVITEONLYCHAN
			|| status == ErrorStatus::ERR_BADCHANNELKEY
			|| status == ErrorStatus::ERR_CHANNELISFULL);
}

void Database::AfterCheck(Event& event) const {
	if (event.get_command() == message::kJoin) {
		if (event.IsChannelEvent()) {
			const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
			if (channel.ContainsUser(event.get_executer())
					&& (!event.HasErrorOccurred() || IsIgnoringErrorOnJoin(event.get_error_status()))) {
						event.set_do_nothing(true);
					}
		}
		return ;
	}
	if (event.get_command() == message::kTopic) {
		if (event.IsChannelEvent()) {
			const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
			//topic <target>
			if (event.get_command_params().size() == 1)
				return ;
			if (!channel.ContainsUser(event.get_executer())) {
				event.set_error_status(ErrorStatus::ERR_NOTONCHANNEL);
				return ;
			}
			if (channel.IsMode('t') && channel.get_members().Contains(&event.get_executer())) {
				event.set_error_status(ErrorStatus::ERR_CHANOPRIVSNEEDED);
				return ;
			}
		}
		std::cout << "event.get_target_num(): " << event.get_target_num() << std::endl;
		if (!event.HasErrorOccurred() && !event.IsChannelEvent()) {
			event.set_error_status(ErrorStatus::ERR_NOSUCHCHANNEL);
			return ;
		}
		return ;
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

	const std::string& new_nickname = event.get_command_params().at(0);
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

	if (event.get_command_params().size() < kParamsSize)
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
	for (std::size_t i = 0; i < kMustNotContain.length(); i++) {
		if (channel_name.find(kMustNotContain[i]) != std::string::npos) {
			event.set_error_status(ErrorStatus::ERR_NOSUCHCHANNEL);
			return ;
		}
	}
}

void Database::CkInviteCommand(Event& event) const {
	(void)event;
	std::cout << "Check vite called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Database::CkKickCommand(Event& event) const {
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
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
	(void)event;
	std::cout << "Check vmsg called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Database::CkModeCommand(Event& event) const {
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}
//check
