#include "user.h"
#include "channel.h"

User::User(int fd) : fd_(fd), is_password_authenticated_(false), is_user_done_(false), is_delete_(false) {
}

User::~User() {
}

void User::CheckCommand(Event& event) const
{
	switch (event.get_command())
	{
		case message::PASS:
			CkPassCommand(event);
			break;
		case message::NICK:
			CkNickCommand(event);
			break;
		case message::USER:
			CkUserCommand(event);
			break;
		case message::JOIN:
			CkJoinCommand(event);
			break;
		case message::INVITE:
			CkInviteCommand(event);
			break;
		case message::KICK:
			CkKickCommand(event);
			break;
		case message::TOPIC:
			CkTopicCommand(event);
			break;
		case message::MODE:
			CkModeCommand(event);
			break;
		case message::PRIVMSG:
			CkPrivmsgCommand(event);
			break;
		default:
			return;
	}
}

std::pair<int, std::string> User::ExecuteCommand(const Event& event)
{
	std::pair<int, std::string> ret_pair;

	switch (event.get_command())
	{
		case message::PASS:
			ret_pair = ExPassCommand(event);
			break;
		case message::NICK:
			ret_pair = ExNickCommand(event);
			break;
		case message::USER:
			ret_pair = ExUserCommand(event);
			break;
		case message::JOIN:
			ret_pair = ExJoinCommand(event);
			break;
		case message::INVITE:
			ret_pair = ExInviteCommand(event);
			break;
		case message::KICK:
			ret_pair = ExKickCommand(event);
			break;
		case message::TOPIC:
			ret_pair = ExTopicCommand(event);
			break;
		case message::MODE:
			ret_pair = ExModeCommand(event);
			break;
		case message::PRIVMSG:
			ret_pair = ExPrivmsgCommand(event);
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

//Execute
std::pair<int, std::string> User::ExPassCommand(const Event& event) {
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

std::pair<int, std::string> User::ExNickCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Nick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ExUserCommand(const Event& event){
	const int kParamsSize = 3;

	std::pair<int, std::string> ret_pair;
	std::vector<std::string> params = event.get_command_params();

	if (event.get_fd() != this->get_fd())
		return ret_pair;
	if (params.size() < kParamsSize)
		ret_pair = std::make_pair(this->get_fd(), "ERR_NEEDMOREPARAMS");
	else if (this->is_user_done_)
		ret_pair = std::make_pair(this->get_fd(), "ERR_ALREADYREGISTRED");
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
	return ret_pair;
}

std::pair<int, std::string> User::ExJoinCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Join method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ExInviteCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Invite method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ExKickCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Kick method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ExTopicCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Topic method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ExPrivmsgCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Privmsg method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}

std::pair<int, std::string> User::ExModeCommand(const Event& event){
	(void)event;
	std::pair<int, std::string> ret_pair;
	std::cout << "Mode method called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
	return ret_pair;
}
//Execute

//Check
void User::CkPassCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkNickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkUserCommand(Event& event) const
{
	(void)event;
	std::cout << "Check User called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkJoinCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Join called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkInviteCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vite called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkKickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkTopicCommand(Event& event) const
{
	(void)event;
	std::cout << "Check opic called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkPrivmsgCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vmsg called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}

void User::CkModeCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::print_string_vector(event.get_command_params());
}
//check


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
