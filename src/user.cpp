#include "user.h"
#include "channel.h"

User::User(){
}

User::User(int fd) : fd_(fd){
	(void)fd_;
	(void)is_password_authenticated_;
}

User::~User(){
}

std::map<int, std::string> User::PassCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Pass method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::NickCommand(Event event){

	std::map<int, std::string> message_map;

	if (event.get_fd() != this->fd_)
		return message_map;

	//パラメータが与えられない場合
	if (event.get_command_params().empty()){
		std::cout << ":No nickname given" << std::endl;
		message_map.insert(std::make_pair(this->fd_, ":No nickname given"));
		return message_map;
	}
	//ニックネームが不適切な場合
	//長さ超過
	std::string new_nickname = event.get_command_params().at(0);
	if (new_nickname.length() > 9){
		std::cout << ":Erroneus nickname" << std::endl;
		message_map.insert(std::make_pair(this->fd_, ":Erroneus nickname"));
		return message_map;
	}
	//ニックネーム設定成功
	//ニックネーム新規登録の場合
	if (this->nickname_.empty()){
		std::cout << "Introducing new nick \"" << new_nickname << "\"" << std::endl;
		message_map.insert(std::make_pair(this->fd_, "Introducing new nick \"" + new_nickname + "\"" ));
	//ニックネーム変更の場合
	} else {
		std::cout << this->nickname_ << " changed his nickname to " << new_nickname << "." << std::endl;
		message_map.insert(std::make_pair(this->fd_, this->nickname_ + " changed his nickname to " + new_nickname  + "."));
	}
	this->nickname_ = new_nickname;
	return message_map;
}

std::map<int, std::string> User::UserCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "User method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::JoinCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Join method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::InviteCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Invite method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::KickCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Kick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::TopicCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Topic method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::PrivmsgCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Privmsg method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}

std::map<int, std::string> User::ModeCommand(Event event){
	(void)event;
	std::map<int, std::string> error_message;
	std::cout << "Mode method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return error_message;
}
