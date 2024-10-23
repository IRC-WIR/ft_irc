#include "user.h"
#include "channel.h"

User::User(int fd) : fd_(fd), is_password_authenticated_(false), is_delete_(false) {
}

User::~User() {
}

void User::CheckCommand(Event& event) const {
	switch (event.get_command()) {
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
			break;
	}
}

OptionalMessage User::ExecuteCommand(const Event& event) {
	switch (event.get_command()) {
		case message::kPass:
			return ExPassCommand(event);
		case message::kNick:
			return ExNickCommand(event);
		case message::kUser:
			return ExUserCommand(event);
		case message::kJoin:
			return ExJoinCommand(event);
		case message::kInvite:
			return ExInviteCommand(event);
		case message::kKick:
			return ExKickCommand(event);
		case message::kTopic:
			return ExTopicCommand(event);
		case message::kMode:
			return ExModeCommand(event);
		case message::kPrivmsg:
			return ExPrivmsgCommand(event);
		default:
			return OptionalMessage::Empty();
	}
}

std::string User::CreateErrorMessage(const message::Command& cmd, const ErrorStatus& err_status) const {
	std::stringstream ret_ss;
	//add error no
	ret_ss << err_status.get_error_code();
	ret_ss << " ";
	//add nick name
	ret_ss << nick_name_;
	ret_ss << " ";
	//add command
	ret_ss << message::MessageParser::get_command_str_map().find(cmd)->second;
	ret_ss << " ";
	//add Error Message
	ret_ss << ": ";
	ret_ss << err_status.get_error_message();
	ret_ss << "\r\n";
	return ret_ss.str();
}

bool User::IsFinished() const {
	//未実装
	return false;
}

//Execute
OptionalMessage User::ExPassCommand(const Event& event) {
	std::pair<int, std::string> ret_pair;

	if (event.get_command_params().size() < 1)
	{
		ret_pair = std::make_pair(event.get_fd(), "ERR_NEEDMOREPARAMS");
	return OptionalMessage::Empty();
	}
	if (is_password_authenticated_)
	{
		ret_pair = std::make_pair(event.get_fd(), "ERR_ALREADYREGISTRED");
	return OptionalMessage::Empty();
	}
	std::cout << "Pass method called!" << std::endl;
	if (server_password_.compare(event.get_command_params()[0]) == 0)
		is_password_authenticated_ = true;
	return OptionalMessage::Empty();
}

OptionalMessage User::ExNickCommand(const Event& event){

	if (event.get_fd() != this->fd_)
		return OptionalMessage::Empty();
	if (event.get_command_params().size() == 0)
		return OptionalMessage::Create(this->fd_, nick_name_ + ":ERR_NONICKNAMEGIVEN");

	std::string new_nickname = event.get_command_params().at(0);
	//ニックネームとして不適切
	if (new_nickname.length() > 9){
		return OptionalMessage::Create(this->fd_, nick_name_ + ":Erroneus nickname");
	}
	//既存ニックネーム：
	//前段階でチェックするが、認証前のユーザが引数のニックネームを持つ場合はエラーとしない)
//	if (event.get_error_status()){
//		return OptionalMessage::Create(this->fd_, nick_name_ + " :Nickname is already in use");
//	}

	std::string ret_message;
	if (this->nick_name_.empty()) {
		ret_message = "Introducing new nick \"" + new_nickname + "\"";
	} else {
		ret_message = this->nick_name_ + " changed his nickname to " + new_nickname + ".";
	}
	this->nick_name_ = new_nickname;
	return OptionalMessage::Create(this->fd_, ret_message);
}

OptionalMessage User::ExUserCommand(const Event& event){
	const int kParamsSize = 3;

	std::pair<int, std::string> ret_pair;
	std::vector<std::string> params = event.get_command_params();

	if (event.get_fd() != this->get_fd())
		return OptionalMessage::Empty();
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
	return OptionalMessage::Empty();
}

OptionalMessage User::ExJoinCommand(const Event& event){
	(void)event;
	std::cout << "Join method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}

OptionalMessage User::ExInviteCommand(const Event& event){
	(void)event;
	std::cout << "Invite method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}

OptionalMessage User::ExKickCommand(const Event& event){
	(void)event;
	std::cout << "Kick method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}

OptionalMessage User::ExTopicCommand(const Event& event){
	(void)event;
	std::cout << "Topic method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}

OptionalMessage User::ExPrivmsgCommand(const Event& event){
	(void)event;
	std::cout << "Privmsg method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}

OptionalMessage User::ExModeCommand(const Event& event){
	(void)event;
	std::cout << "Mode method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}
//Execute

//Check
void User::CkPassCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Pass called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkNickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkUserCommand(Event& event) const
{
	(void)event;
	std::cout << "Check User called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkJoinCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Join called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkInviteCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vite called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkKickCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkTopicCommand(Event& event) const
{
	(void)event;
	std::cout << "Check opic called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkPrivmsgCommand(Event& event) const
{
	(void)event;
	std::cout << "Check vmsg called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkModeCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
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

bool	User::IsVerified() const
{
	if (!this->is_password_authenticated_
		|| this->nick_name_.empty()
		|| this->user_name_.empty()){
		return false;
	}
	return true;
}
