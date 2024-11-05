#include "user.h"
#include "channel.h"
#include "channel_event.h"
#include <poll.h>

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

	const Command& command = event->get_command();

	if (command == Command::kPass)
		CkPassCommand(*event);
	else if (command == Command::kNick)
		CkNickCommand(*event);
	else if (command == Command::kUser)
		CkUserCommand(*event);
	else if (command == Command::kJoin)
		CkJoinCommand(*event);
	else if (command == Command::kInvite)
		CkInviteCommand(*event);
	else if (command == Command::kKick)
		CkKickCommand(*event);
	else if (command == Command::kTopic)
		CkTopicCommand(*event);
	else if (command == Command::kMode)
		CkModeCommand(*event);
	else if (command == Command::kPrivmsg)
		CkPrivmsgCommand(*event);
	else if (command == Command::kQuit)
		CkQuitCommand(*event);

}

OptionalMessage User::ExecuteCommand(const Event& event) {
	const Command& command = event.get_command();

	if (command == Command::kPass)
		return ExPassCommand(event);
	else if (command == Command::kNick)
		return ExNickCommand(event);
	else if (command == Command::kUser)
		return ExUserCommand(event);
	else if (command == Command::kJoin)
		return ExJoinCommand(event);
	else if (command == Command::kInvite)
		return ExInviteCommand(event);
	else if (command == Command::kKick)
		return ExKickCommand(event);
	else if (command == Command::kTopic)
		return ExTopicCommand(event);
	else if (command == Command::kMode)
		return ExModeCommand(event);
	else if (command == Command::kPrivmsg)
		return ExPrivmsgCommand(event);
	else if (command == Command::kQuit)
		return ExQuitCommand(event);
	else
		return OptionalMessage::Empty();

}

std::string User::CreateErrorMessage(const Command& cmd, const ErrorStatus& error_status) const {
	std::stringstream ss;
	//add hostname
	ss << ":";
	ss << utils::kHostName;
	ss << " ";
	//add error no
	ss << error_status.get_code();
	ss << " ";
	//add nick name
	ss << (nick_name_.empty()? "*" : nick_name_) ;
	ss << " ";
	//add command
	ss << cmd.get_name();
	ss << " ";
	//add Error Message
	ss << ":";
	ss << error_status.get_message();
	ss << "\r\n";
	return ss.str();
}

std::string User::CreateMessage(const User& from, const std::string& target, const Command& cmd, const std::vector<std::string>& params) const {
	std::stringstream ss;
	// from hostname
	ss << from.CreateNameWithHost();
	ss << " ";
	// command
	ss << cmd.get_name();
	ss << " ";
	// to name
	ss << target;
	ss << " ";
	//add message
	ss << ":";
	//パラメータ１個目を飛ばす（ターゲットになるので）
	for (std::vector<std::string>::const_iterator it = ++params.begin();
		it != params.end();
		it ++) {
			ss << *it <<  " ";
		}
	ss << "\r\n";
	return ss.str();
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
		return OptionalMessage::Create(get_fd(), utils::GetWelcomeString(ResponseStatus::RPL_WELCOME, event.get_executer()));
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
			return OptionalMessage::Create(get_fd(), utils::GetWelcomeString(ResponseStatus::RPL_WELCOME, event.get_executer()));
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
	this->real_name_ = utils::Join(params.begin() + 2, params.end(), " ");
	if (IsVerified() && !this->is_displayed_welcome()) {
		set_displayed_welcome(true);
		return OptionalMessage::Create(get_fd(), utils::GetWelcomeString(ResponseStatus::RPL_WELCOME, event.get_executer()));
	}
	return OptionalMessage::Empty();
}

static std::string GenerateJoinCommonMessage(const User& target, const Channel& channel) {
	std::stringstream ss;

	ss << target.CreateNameWithHost() << " ";
	ss << Command::kJoin.get_name() << " :";
	ss << channel.get_name() << "\r\n";
	return ss.str();
}

std::string User::GenerateJoinDetailMessage(const Channel& channel) const {
	std::stringstream ss;
	// topic
	if (!channel.get_topic().empty())
		ss << ":" << utils::kHostName << " "
			<< 332 << " "
			<< this->get_nick_name() << " "
			<< channel.get_name() << " :"
			<< channel.get_topic() << "\r\n";
	// メンバーリスト
	ss << ":" << utils::kHostName << " ";
	ss << 353 << " "
		<< this->get_nick_name() << " = "
		<< channel.get_name() << " :"
		<< channel.GenerateMemberListWithNewUser(*this) << "\r\n";
	// End of NAMES list
	ss << ":" << utils::kHostName << " ";
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

static bool IsRPL(const Event& event) {
	return event.get_command_params().size() == 1;
}

std::string User::CreateTopicRplMessage(const Channel& channel) const {
	bool has_topic = !channel.get_topic().empty();
	std::stringstream ss;
	ss << ":";
	ss << utils::kHostName;
	ss << " ";
	// response no
	ss << (has_topic ? ResponseStatus::RPL_TOPIC.get_code() :  ResponseStatus::RPL_NOTOPIC.get_code()) ;
	ss << " ";
	// nick name
	ss << (nick_name_.empty()? "*" : nick_name_) ;
	ss << " ";
	// channel name
	ss << (channel.get_name()) ;
	ss << " ";
	// error message
	ss << ":";
	ss << (has_topic ? channel.get_topic()  : ResponseStatus::RPL_NOTOPIC.get_message());
	ss << "\r\n";
	return ss.str();
}

static std::string GenerateTopicMessage(const User& user, const Channel& channel,const Event& event) {
	std::stringstream ss;
	ss << ":" << user.get_nick_name() << "!" << user.get_user_name() <<  "@"
		<< utils::kHostName << " ";
	// nick name
	ss << user.get_nick_name();
	ss << " ";
	// command
	ss << Command::kTopic.get_name();
	ss << " ";
	// channel name
	ss << channel.get_name();
	ss << " ";
	// channel topic name(get from event because channel topic setted is uncertain)
	ss << ":";
	ss << event.get_command_params()[1];
	ss << "\r\n";
	return ss.str();
}

OptionalMessage User::ExTopicCommand(const Event& event) {
	if (event.HasErrorOccurred()) {
		if (event.get_fd() == this->get_fd()) {
			const std::string& error_msg = CreateErrorMessage(event.get_command(), event.get_error_status());
			return OptionalMessage::Create(event.get_fd(), error_msg);
		}
		return OptionalMessage::Empty();
	}
	if (!event.IsChannelEvent())
		return OptionalMessage::Empty();
	//topic <target>
	if (IsRPL(event)) {
		const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
		const std::string& rpl_msg = CreateTopicRplMessage(channel);
		return OptionalMessage::Create(event.get_fd(), rpl_msg);
	}
	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	const std::string common_message = GenerateTopicMessage(event.get_executer(), channel, event);
	if (this->joining_channels_.Contains(&channel))
		return OptionalMessage::Create(this->get_fd(), common_message);
	else
		return OptionalMessage::Empty();
}

OptionalMessage User::ExPrivmsgCommand(const Event& event) {
	//失敗
	if (event.HasErrorOccurred()) {
		if (event.get_fd() != this->get_fd())
			return OptionalMessage::Empty();
		const std::string& err_msg = CreateErrorMessage(event.get_command(), event.get_error_status());
		return OptionalMessage::Create(this->get_fd(), err_msg);
	}
	//成功
	//送信相手確認
	const std::vector<std::string>& params = event.get_command_params();
	const std::string& target = params[0];
	if (IsTarget(target, event)) {
		const std::string& send_msg = CreateMessage(event.get_executer(), target, event.get_command(), params);
		return OptionalMessage::Create(this->get_fd(), send_msg);
	}
	return OptionalMessage::Empty();
}

OptionalMessage User::ExModeCommand(const Event& event){
	(void)event;
	std::cout << "Mode method called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
	return OptionalMessage::Empty();
}

OptionalMessage User::ExQuitCommand(const Event& event){
	if (event.get_fd() == this->get_fd()) {
		this->is_delete_ = true;
		return OptionalMessage::Empty();
	}
	const User& executer = event.get_executer();
	std::string prefix_message = executer.get_nick_name() + " QUIT : ";
	for (std::vector<const Channel*>::iterator it =
	this->joining_channels_.begin();
	it != this->joining_channels_.end();
	++it) {
		if((*it)->ContainsUser(executer)) {
			std::string context_message;
			if (event.get_event_type() == POLLHUP)
				context_message = "client dies and EOF occurs on socket";
			else if (event.get_command_params().empty())
				context_message = "client quit";
			else
				context_message = event.get_command_params()[0];
			return OptionalMessage::Create(this->fd_, prefix_message + context_message + "\r\n");
		}
	}
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
		if (utils::StrToLower(this->nick_name_) == utils::StrToLower(new_nickname)){
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
	(void) event;
}

void User::CkPrivmsgCommand(Event& event) const
{
	if (event.get_command_params()[0] != this->get_nick_name())
		return ;
	event.add_target_num();
}

void User::CkModeCommand(Event& event) const
{
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void User::CkQuitCommand(Event& event) const
{
	(void)event;
	return ;
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

bool User::get_is_delete() const {
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

//<nick>!<user>@<host>
std::string User::CreateNameWithHost() const {
	std::stringstream ss;
	ss << ":" << this->get_nick_name();
	ss << "!" << this->get_user_name();
	ss << "@" << utils::kHostName;
	return ss.str();
}

bool User::IsVerified() const
{
	if (!this->is_password_authenticated_
		|| this->nick_name_.empty()
		|| this->user_name_.empty()){
		return false;
	}
	return true;
}


bool User::IsTarget(const std::string& target, const Event& event) const
{
	if (target == this->get_nick_name())
		return true;
	if (event.IsChannelEvent()) {
		const ChannelEvent& channel_event = dynamic_cast<const ChannelEvent&>(event);
		return channel_event.get_channel().ContainsUser(*this);
	}
	return false;
}