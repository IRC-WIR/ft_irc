#include "database.h"
#include "message.h"

Database::Database(){};
Database::~Database(){};

void Database::CreateUser(int fd) {
	try {
		User* user = new User(fd);
		check_element_.push_back(user);
		execute_element_.push_back(user);
	} catch(const std::bad_alloc& e) {
		std::cerr << "bad to alloc memory" << e.what() << '\n';
	}
}

void Database::CheckEvent(Event& event) const {
	Database::CheckCommandAndParams(event);
	if (event.HasErrorOccurred())
		return ;
	std::size_t vector_length = check_element_.size();
	for (std::size_t i = 0; i < vector_length; i++)
		check_element_[i] -> CheckCommand(event);
}

std::map<int, std::string>	Database::ExecuteEvent(const Event& event) {
	std::map<int, std::string> ret;
	std::size_t vector_length = execute_element_.size();
	for (size_t i = 0; i < vector_length; i++) {
		OptionalMessage message = execute_element_[i] -> ExecuteCommand(event);
		if (!message.IsEmpty())
			ret.insert(message.MakePair());
	}
	return ret;
}

void Database::DeleteFinishedElements() {
	std::set<Finishable *> ptr_set;

	Database::EraseAndAdd(check_element_, ptr_set);
	Database::EraseAndAdd(execute_element_, ptr_set);

	for (std::set<Finishable *>::iterator it = ptr_set.begin(); it != ptr_set.end(); ++it)
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

//Check
void Database::CkPassCommand(Event& event) const {
	(void)event;
	std::cout << "Check Pass called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Database::CkNickCommand(Event& event) const {

	const int kParamsSize = 1;

	if (event.get_command_params().size() < kParamsSize) {
		event.set_error_status(ErrorStatus::ERR_NONICKNAMEGIVEN);
		return ;	
	}

	std::string new_nickname = event.get_command_params().at(0);
	if (new_nickname.length() > 9) {
		event.set_error_status(ErrorStatus::ERR_ERRONEUSNICKNAME);
		return ;
	}

	char must_not_contain[] = {' ', ',', '*', '?', '!', '@', '.'};
	const int must_not_contain_size = sizeof(must_not_contain) / sizeof(char);
	for (int i = 0; i < must_not_contain_size; i++) {
		if (new_nickname.find(must_not_contain[i]) != std::string::npos) {
			event.set_error_status(ErrorStatus::ERR_ERRONEUSNICKNAME);
			return;
		}
	}

	char must_not_start_with[] = {'$', ':', '&', '#', '~' , '%', '+'};
	const int must_not_start_with_size = sizeof(must_not_start_with) / sizeof(char);
	for (int i = 0; i < must_not_start_with_size; i++) {
		if (new_nickname[0] == must_not_start_with[i]) {
			event.set_error_status(ErrorStatus::ERR_ERRONEUSNICKNAME);	
			return;
		}
	}

	return;
}

void Database::CkUserCommand(Event& event) const {
	(void)event;
	std::cout << "Check User called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Database::CkJoinCommand(Event& event) const {
	(void)event;
	std::cout << "Check Join called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
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
	(void)event;
	std::cout << "Check opic called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
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
