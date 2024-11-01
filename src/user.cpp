#include "user.h"
#include "channel.h"
#include "channel_event.h"

User::User(int fd) :
	fd_(fd), is_password_authenticated_(false),
	is_delete_(false),
	is_displayed_welcome_(false) {
}

User::~User() {
}

void User::CheckCommand(Event*& event) const {
	if (event->get_fd() == this->get_fd())
		event->set_executer(*this);

	switch (event->get_command()) {
		case message::kPass:
			CkPassCommand(*event);
			break;
		case message::kNick:
			CkNickCommand(*event);
			break;
		case message::kUser:
			CkUserCommand(*event);
			break;
		case message::kJoin:
			CkJoinCommand(*event);
			break;
		case message::kInvite:
			CkInviteCommand(*event);
			break;
		case message::kKick:
			CkKickCommand(*event);
			break;
		case message::kTopic:
			CkTopicCommand(*event);
			break;
		case message::kMode:
			CkModeCommand(*event);
			break;
		case message::kPrivmsg:
			CkPrivmsgCommand(*event);
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
	ret_ss << (nick_name_.empty()? "*" : nick_name_) ;
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
	return is_delete_;
}

//Execute
OptionalMessage User::ExPassCommand(const Event& event) {
	if (event.get_fd() != this->get_fd())
		return OptionalMessage::Empty();
	if (event.HasErrorOccurred()) {
		const std::string& err_msg = CreateErrorMessage(event.get_command(), event.get_error_status());
		return OptionalMessage::Create(event.get_fd(), err_msg);
	}
	set_is_password_authenticated(true);
	if (IsVerified() && !this->is_displayed_welcome()) {
		set_displayed_welcome(true);
		return OptionalMessage::Create(get_fd(), utils::GetWelcomeString());
	}
	return OptionalMessage::Empty();
}

OptionalMessage User::ExNickCommand(const Event& event){

	if (event.get_fd() != this->get_fd())
		return OptionalMessage::Empty();

	if (event.HasErrorOccurred()) {
		return OptionalMessage::Create(this->get_fd(), CreateErrorMessage(event.get_command(), event.get_error_status()));
	}

	const std::string& new_nickname = event.get_command_params()[0];
	std::string ret_message;
	if (this->nick_name_.empty()) {
		ret_message = "Introducing new nick \"" + new_nickname + "\"\n";
	} else {
		ret_message = this->nick_name_ + " changed his nickname to " + new_nickname + ".\n";
	}
	this->nick_name_ = new_nickname;
	if (IsVerified()) {
		if (!this->is_displayed_welcome()) {
			set_displayed_welcome(true);
			return OptionalMessage::Create(get_fd(), utils::GetWelcomeString());
		}
		return OptionalMessage::Create(get_fd(), ret_message);
	}
	return OptionalMessage::Empty();
}

OptionalMessage User::ExUserCommand(const Event& event) {
	if (event.get_fd() != this->get_fd())
		return OptionalMessage::Empty();
	if (event.HasErrorOccurred()) {
		const std::string& message = User::CreateErrorMessage(event.get_command(), event.get_error_status());
		return OptionalMessage::Create(this->get_fd(), message);
	}

	const std::vector<std::string>& params = event.get_command_params();
	// 今回は1,2番目の要素(= 2, 3番目の引数)は無視する
	this->user_name_ = params[0];
	for (std::vector<std::string>::size_type i = 3; i < params.size(); i++) {
		if (i != 3)
			this->real_name_ += " ";
		this->real_name_ += params[i];
	}
	if (IsVerified() && !this->is_displayed_welcome()) {
		set_displayed_welcome(true);
		return OptionalMessage::Create(get_fd(), utils::GetWelcomeString());
	}
	return OptionalMessage::Empty();
}

static std::string GenerateJoinCommonMessage(const User& target, const Channel& channel) {
	std::stringstream ss;
	ss << target.get_nick_name() << " "
		<< message::MessageParser::get_command_str_map().find(message::kJoin)->second << " :"
		<< channel.get_name() << "\r\n";
	return ss.str();
}

std::string User::GenerateJoinDetailMessage(const Channel& channel) const {
	std::stringstream ss;
	// topic
	if (!channel.get_topic().empty())
		ss << 332 << " "
			<< this->get_nick_name() << " "
			<< channel.get_name() << " :"
			<< channel.get_topic() << "\r\n";
	// メンバーリスト
	ss << 353 << " "
		<< this->get_nick_name() << " = "
		<< channel.get_name() << " :"
		<< channel.GenerateMemberListWithNewUser(*this) << "\r\n";
	// End of NAMES list
	ss << 366 << " "
		<< this->get_nick_name() << " "
		<< channel.get_name() << " :"
		<< "End of /NAMES list." << "\r\n";
	return ss.str();
}

OptionalMessage User::ExJoinCommand(const Event& event) {
	if (event.HasErrorOccurred()) {
		if (event.get_fd() == this->get_fd()) {
			const std::string& message = User::CreateErrorMessage(event.get_command(), event.get_error_status());
			return OptionalMessage::Create(this->get_fd(), message);
		} else
			return OptionalMessage::Empty();
	}
	if (!event.IsChannelEvent())
		return OptionalMessage::Empty();
	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	const std::string common_message = GenerateJoinCommonMessage(event.get_executer(), channel);
	if (event.get_fd() == this->get_fd()) {
		this->joining_channels_.push_back(&channel);
		return OptionalMessage::Create(this->get_fd(), common_message + this->GenerateJoinDetailMessage(channel));
	}
	if (this->joining_channels_.Contains(&channel))
		return OptionalMessage::Create(this->get_fd(), common_message);
	else
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
	if (event.get_fd() != this->get_fd())
		return ;
	if (event.HasErrorOccurred())
		return ;
	if (get_is_password_authenticated())
		event.set_error_status(ErrorStatus::ERR_ALREADYREGISTRED);
	return;
}

void User::CkNickCommand(Event& event) const
{
		if (event.HasErrorOccurred())
			return ;
		const std::string& new_nickname = event.get_command_params()[0];
		if (this->nick_name_ == new_nickname){
			event.set_error_status(ErrorStatus::ERR_NICKNAMEINUSE);
		}
	return ;
}

void User::CkUserCommand(Event& event) const {
	if (event.get_fd() != this->get_fd()
			|| event.HasErrorOccurred())
		return ;
	if (!this->user_name_.empty())
		event.set_error_status(ErrorStatus::ERR_ALREADYREGISTRED);
}

void User::CkJoinCommand(Event& event) const {
	if (event.get_fd() != this->get_fd()
			|| event.HasErrorOccurred())
		return ;
	if (this->joining_channels_.size() >= Channel::kMaxJoiningChannels) {
		event.set_error_status(ErrorStatus::ERR_TOOMANYCHANNELS);
		return ;
	}
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

void User::set_is_password_authenticated(bool is_pw_authenticated) {
	is_password_authenticated_ = is_pw_authenticated;
}

bool User::get_is_password_authenticated() const {
	return is_password_authenticated_;
}

void User::set_displayed_welcome(bool is_verified) {
	is_displayed_welcome_ = is_verified;
}

bool User::is_displayed_welcome(void) const {
	return is_displayed_welcome_;
}

int User::get_fd() const
{
	return fd_;
}

bool User::get_is_delete() const
{
	return is_delete_;
}

const std::string& User::get_nick_name() const {
	return this->nick_name_;
}

const std::string& User::get_user_name() const {
	return this->user_name_;
}

const std::string& User::get_real_name() const {
	return this->real_name_;
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
