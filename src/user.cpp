#include "user.h"
#include "channel.h"

User::User(int fd) : fd_(fd), is_password_authenticated_(false), is_delete_(false) {
}

User::~User() {
}

void User::CheckCommand(Event& event) const
{
	//未実装
	(void)event;
}

std::pair<int, std::string> User::ExecuteCommand(const Event& event)
{
	std::pair<int, std::string> ret_pair;

	switch (event.get_command())
	{
		case message::PASS:
			ret_pair = PassCommand(event);
			break;
		case message::NICK:
			ret_pair = NickCommand(event);
			break;
		case message::USER:
			ret_pair = UserCommand(event);
			break;
		case message::JOIN:
			ret_pair = JoinCommand(event);
			break;
		case message::INVITE:
			ret_pair = InviteCommand(event);
			break;
		case message::KICK:
			ret_pair = KickCommand(event);
			break;
		case message::TOPIC:
			ret_pair = TopicCommand(event);
			break;
		case message::MODE:
			ret_pair = ModeCommand(event);
			break;
		case message::PRIVMSG:
			ret_pair = PrivmsgCommand(event);
			break;
		default:
			return ret_pair;
	}
	return ret_pair;
}

bool User::is_finished() const
{
	//未実装
	return true;
}


std::pair<int, std::string> User::PassCommand(const Event& event) {
	std::pair<int, std::string> ret_pair;

	if (event.get_command_params().size() < 1)
	{
		ret_pair = std::make_pair(event.get_fd(), "ERR_NEEDMOREPARAMS");
		return ret_pair;
	}
	if (is_password_authenticated_)
	{
		ret_pair = std::make_pair(event.get_fd(), "ERR_ALREADYREGISTRED");
		return ret_pair;
	}
	std::cout << "Pass method called!" << std::endl;
	if (server_password_.compare(event.get_command_params()[0]) == 0)
		is_password_authenticated_ = true;
	return ret_pair;
}

std::pair<int, std::string> User::NickCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Nick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::UserCommand(const Event& event){
	const int kParamsSize = 3;

	std::pair<int, std::string> ret_pair;
	std::vector<std::string> params = event.get_command_params();

	if (event.get_fd() != this->get_fd())
		return ret_pair;
	if (params.size() < kParamsSize)
		ret_pair = std::make_pair(this->get_fd(), "ERR_NEEDMOREPARAMS");
	else if (this->is_verified())
		ret_pair = std::make_pair(this->get_fd(), "ERR_ALREADYREGISTRED");
	else {
		this->user_name_ = params[0];
		// 今回は1,2番目の要素は無視する
		for (std::vector<std::string>::size_type i = 3; i < params.size(); i++) {
			if (i != 3)
				this->real_name_ += " ";
			this->real_name_ += params[i];
		}
	}
	return ret_pair;
}

std::pair<int, std::string> User::JoinCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Join method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::InviteCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Invite method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::KickCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Kick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::TopicCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Topic method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::PrivmsgCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Privmsg method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ModeCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Mode method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
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

bool	User::is_verified() const
{
	if (!this->is_password_authenticated_
		|| this->nick_name_.empty()
		|| this->user_name_.empty()){
		return false;
	}
	return true;
}
