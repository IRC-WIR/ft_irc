#include "user.h"
#include "channel.h"

User::User(){
}

User::User(int fd) : fd_(fd), is_password_authenticated_(false){
	(void)fd_;
	(void)is_password_authenticated_;
}

User::~User(){
}

std::map<int, std::string> User::PassCommand(Event& event) {
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

std::map<int, std::string> User::NickCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Nick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::UserCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "User method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::JoinCommand(Event& event){
	std::map<int, std::string> ret_map;

	if (event.is_error_occurred())
		ret_map.insert(std::make_pair(event.get_fd(), event.get_error_message()));
	else
		this->channels_.push_back(event.get_channel());
	return ret_map;
}

std::map<int, std::string> User::InviteCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Invite method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::KickCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Kick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::TopicCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Topic method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::PrivmsgCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Privmsg method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::ModeCommand(Event& event){
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