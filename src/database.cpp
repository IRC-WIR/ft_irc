#include "database.h"
#include "message.h"

Database::Database(const std::string& password):server_password_(password){};
Database::~Database(){};

void Database::CreateUser(int fd) {
	try {
		User* user = new User(fd);
		user->set_server_password(server_password_);
		check_element_.push_back(user);
		execute_element_.push_back(user);
	} catch(const std::bad_alloc& e) {
		std::cerr << "bad to alloc memory" << e.what() << std::endl;
	} catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}
}

void Database::CheckEvent(Event& event) const {
	Database::CheckCommandAndParams(event);
	std::size_t vector_length = check_element_.size();

	for (std::size_t i = 0; i < vector_length; i++)
		check_element_[i] -> CheckCommand(event);
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
	std::set<const Finishable*> ptr_set;

	Database::EraseAndAdd(check_element_, ptr_set);
	Database::EraseAndAdd(execute_element_, ptr_set);
	for (std::set<const Finishable*>::iterator it = ptr_set.begin(); it != ptr_set.end(); ++it)
	{
		if ((*it)->IsFinished())
			delete *it;
	}
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
	const int kParamsSize = 1;

	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() < kParamsSize)
	{
		event.set_error_status(ErrorStatus::ERR_NEEDMOREPARAMS);
		return;
	}
	if (params[0].compare(get_server_password()) != 0)
		event.set_error_status(ErrorStatus::ERR_PASSWDMISMATCH);
}

void Database::CkNickCommand(Event& event) const {
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
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
