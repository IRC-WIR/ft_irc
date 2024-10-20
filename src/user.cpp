#include "user.h"
#include "channel.h"

User::User(int fd) : fd_(fd), is_password_authenticated_(false), is_delete_(false) {
}

User::~User() {
}

void User::CheckCommand(Event& event) const
{
	switch (event.get_command())
	{
		case message::kPass:
			CkPassCommand(event);
			break;
		case message::kNick:
			CkNickCommand(event);
			break;
		case message::kUser:
			CkUserCommand(event);
			break;
		case message::kJoin:
			CkJoinCommand(event);
			break;
		case message::kInvite:
			CkInviteCommand(event);
			break;
		case message::kKick:
			CkKickCommand(event);
			break;
		case message::kTopic:
			CkTopicCommand(event);
			break;
		case message::kMode:
			CkModeCommand(event);
			break;
		case message::kPrivmsg:
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
		case message::kPass:
			ret_pair = ExPassCommand(event);
			break;
		case message::kNick:
			ret_pair = ExNickCommand(event);
			break;
		case message::kUser:
			ret_pair = ExUserCommand(event);
			break;
		case message::kJoin:
			ret_pair = ExJoinCommand(event);
			break;
		case message::kInvite:
			ret_pair = ExInviteCommand(event);
			break;
		case message::kKick:
			ret_pair = ExKickCommand(event);
			break;
		case message::kTopic:
			ret_pair = ExTopicCommand(event);
			break;
		case message::kMode:
			ret_pair = ExModeCommand(event);
			break;
		case message::kPrivmsg:
			ret_pair = ExPrivmsgCommand(event);
			break;
		default:
			break;
	}
	return ret_pair;
}

std::string User::CreateErrorMessage(const message::Command& cmd, const ErrorStatus& err_status) const
{
	std::string ret_str;
	//add error no
	ret_str += utils::ft_itos(err_status.get_error_code());
	ret_str += " ";
	//add nick name
	ret_str += nick_name_;
	ret_str += " ";
	//add command
	ret_str += message::MessageParser::get_command_str_map().find(cmd)->second;
	ret_str += " ";
	//add Error Message
	ret_str += ": ";
	ret_str += err_status.get_error_message();
	ret_str += "\r\n";
	return ret_str;
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
	else if (!this->user_name_.empty())
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

bool	User::is_verified() const
{
	if (!this->is_password_authenticated_
		|| this->nick_name_.empty()
		|| this->user_name_.empty()){
		return false;
	}
	return true;
}
