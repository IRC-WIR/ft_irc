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

	std::map<int, std::string> message_map;

	if (event.get_fd() != this->fd_)
		return message_map;
	if (event.get_start_listener_result() != DEFAULT)
		return message_map;
	
	//ニックネームが不適切な場合
	//長さ超過
	////only for now
	if (event.get_command_params().size() < 1)
		return message_map;
	////
	std::string new_nickname = event.get_command_params().at(0);
	if (new_nickname.length() > 9){
		std::cout << new_nickname << ":Erroneus nickname" << std::endl;
		message_map.insert(std::make_pair(this->fd_, new_nickname + ":Erroneus nickname"));
		return message_map;
	}
	//ニックネーム設定成功
	//ニックネーム新規登録の場合
	if (this->nick_name_.empty()){
		std::cout << "Introducing new nick \"" << new_nickname << "\"" << std::endl;
		message_map.insert(std::make_pair(this->fd_, "Introducing new nick \"" + new_nickname + "\"" ));
	//ニックネーム変更の場合
	} else {
		std::cout << this->nick_name_ << " changed his nickname to " << new_nickname << "." << std::endl;
		message_map.insert(std::make_pair(this->fd_, this->nick_name_ + " changed his nickname to " + new_nickname  + "."));
	}
	this->nick_name_ = new_nickname;
	return message_map;
}

std::map<int, std::string> User::UserCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "User method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::JoinCommand(Event& event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Join method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
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

std::string User::get_nick_name() const
{
	return nick_name_;
}
