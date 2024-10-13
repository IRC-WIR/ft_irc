#include "user.h"

User::User(int fd) : fd_(fd), is_password_authenticated_(false), is_user_done_(false), is_delete_(false) {
}

User::~User() {
}

void User::CheckCommand(Event& event) const
{
	//未実装
	(void)event;
}

std::pair<int, std::string>* User::ExecuteCommand(const Event& event)
{
	//未実装
	std::pair<int, std::string>* ret_pair = new std::pair<int, std::string>();
	(void)event;
	return ret_pair;
}

bool User::is_finished() const
{
	//未実装
	return true;
}


std::map<int, std::string> User::PassCommand(const Event& event) {
	std::map<int, std::string> ret_map;
	std::pair<int, std::string> ret_pair;

	ret_map.clear();
	if (event.get_command_params().size() < 1)
	{
		ret_pair = std::make_pair(event.get_fd(), "ERR_NEEDMOREPARAMS");
		ret_map.insert(ret_pair);
		return ret_map;
	}
	if (is_password_authenticated_)
	{
		ret_pair = std::make_pair(event.get_fd(), "ERR_ALREADYREGISTRED");
		ret_map.insert(ret_pair);
		return ret_map;
	}
	std::cout << "Pass method called!" << std::endl;
	if (server_password_.compare(event.get_command_params()[0]) == 0)
		is_password_authenticated_ = true;
	return ret_map;
}

std::map<int, std::string> User::NickCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Nick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::UserCommand(const Event& event){
	const int kParamsSize = 3;

	std::map<int, std::string> ret_map;
	std::vector<std::string> params = event.get_command_params();

	if (event.get_fd() != this->get_fd())
		return ret_map;
	if (params.size() < kParamsSize)
		ret_map.insert(std::make_pair(this->get_fd(), "ERR_NEEDMOREPARAMS"));
	else if (this->is_user_done_)
		ret_map.insert(std::make_pair(this->get_fd(), "ERR_ALREADYREGISTRED"));
	else {
		this->is_user_done_ = true;
		this->user_name_ = params[0];
		// 今回は1,2番目の要素は無視する
		for (std::vector<std::string>::size_type i = 3; i < params.size(); i++) {
			if (i != 3)
				this->real_name_ += " ";
			this->real_name_ += params[i];
		}
	}
	return ret_map;
}

std::map<int, std::string> User::JoinCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Join method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::InviteCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Invite method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::KickCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Kick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::TopicCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Topic method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::PrivmsgCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Privmsg method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::ModeCommand(const Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Mode method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

void User::set_server_password(const std::string& password)
{
	server_password_ = password;
}

bool User::get_is_password_authenticated() const
{
	return is_password_authenticated_;
}

int User::get_fd() const
{
	return fd_;
}

bool User::get_is_delete() const
{
	return is_delete_;
}
