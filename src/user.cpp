#include "user.h"
#include "channel.h"
#include "channel_event.h"
#include "mode.h"
#include <poll.h>

User::User(int fd) :
	fd_(fd), is_password_authenticated_(false),
	is_delete_(false),
	is_displayed_welcome_(false) {
}

User::~User() {
}

std::string User::CreateCommonMessage(const Command& command, const std::vector<std::string>& messages) const {
	std::stringstream ss;

	ss << this->CreateNameWithHost() << " ";
	ss << command.get_name();
	if (!messages.empty()) {
		if (messages.size() > 1)
			ss << " " << utils::Join(messages.begin(), messages.end() - 1, " ");
		ss << " :" << messages.back();
	}
	ss << utils::kNewLine;
	return ss.str();
}

std::string User::CreateReplyMessage(int code, const std::vector<std::string>& messages) const {
	std::stringstream ss;

	ss << ":" << utils::kHostName;
	ss << " " << code;
	ss << " " << this->get_nick_name();
	if (!messages.empty()) {
		if (messages.size() > 1)
			ss << " " << utils::Join(messages.begin(), messages.end() - 1, " ");
		ss << " :" << messages.back();
	}
	ss << utils::kNewLine;
	return ss.str();
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
	ss << utils::kNewLine;
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
		return OptionalMessage::Create(this->get_fd(),
				User::CreateErrorMessage(event.get_command(), event.get_error_status()));
	}

	const std::vector<std::string>& params = event.get_command_params();
	// 今回は1,2番目の要素(= 2, 3番目の引数)は無視する
	this->user_name_ = params[0];
	this->real_name_ = utils::Join(params.begin() + 2, params.end(), " ");
	if (this->IsVerified() && !this->is_displayed_welcome()) {
		this->set_displayed_welcome(true);
		return OptionalMessage::Create(this->get_fd(),
				utils::GetWelcomeString(ResponseStatus::RPL_WELCOME, *this));
	}
	return OptionalMessage::Empty();
}

std::string User::CreateJoinDetailMessage(const Channel& channel) const {
	std::stringstream ss;
	// topic
	if (!channel.get_topic().empty())
		ss << ":" << utils::kHostName << " "
			<< 332 << " "
			<< this->get_nick_name() << " "
			<< channel.get_name() << " :"
			<< channel.get_topic() << utils::kNewLine;
	// メンバーリスト
	ss << ":" << utils::kHostName << " ";
	ss << 353 << " "
		<< this->get_nick_name() << " = "
		<< channel.get_name() << " :"
		<< channel.GenerateMemberListWithNewUser(*this) << utils::kNewLine;
	// End of NAMES list
	ss << ":" << utils::kHostName << " ";
	ss << 366 << " "
		<< this->get_nick_name() << " "
		<< channel.get_name() << " :"
		<< "End of /NAMES list." << utils::kNewLine;
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
	std::vector<std::string> messages;
	messages.push_back(channel.get_name());
	const std::string common_message = event.get_executer().CreateCommonMessage(event.get_command(), messages);
	if (event.get_fd() == this->get_fd()) {
		this->joining_channels_.push_back(&channel);
		return OptionalMessage::Create(this->get_fd(), common_message + this->CreateJoinDetailMessage(channel));
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
	//失敗
	if (event.HasErrorOccurred()) {
		if (event.get_fd() == this->get_fd()) {
			const std::string& message = User::CreateErrorMessage(event.get_command(), event.get_error_status());
			return OptionalMessage::Create(this->get_fd(), message);
		}
		return OptionalMessage::Empty();
	}
	if (!event.IsChannelEvent()) {
		if (event.get_fd() == this->get_fd()) {
			const std::string& message = User::CreateErrorMessage(event.get_command(), ErrorStatus::ERR_NOSUCHCHANNEL);
			return OptionalMessage::Create(this->get_fd(), message);
		}
		return OptionalMessage::Empty();
	}
	//成功
	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	const std::string& target_name = event.get_command_params()[1];
	//対象チャンネルに所属している場合
	if (channel.ContainsUser(*this)) {
		std::string base_message;
		if (event.get_fd() == this->get_fd()) {
			base_message = "Kick " + target_name + " from " + channel.get_name();
		} else {
			base_message = "Kick message from " + event.get_executer().get_nick_name() + " to remove " + target_name + " from channel " + channel.get_name();
		}
		const std::vector<std::string>& params = event.get_command_params();
		std::string optional_message = "";
		if (params.size() > 2)
			optional_message = " using \"" + utils::Join(params.begin() + 2, params.end(), " ") + "\" as the reason(comment)";
		return OptionalMessage::Create(this->get_fd(), base_message + optional_message + "\r\n");
	}
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

OptionalMessage User::ExModeCommand(const Event& event) {
	const int kKeyMaxLength = 32;
	const std::vector<std::string>& params = event.get_command_params();

	if (event.HasErrorOccurred()) {
		if (event.get_fd() != this->get_fd())
			return OptionalMessage::Empty();
		return OptionalMessage::Create(this->get_fd(),
				User::CreateErrorMessage(event.get_command(), event.get_error_status()));
	}
	if (!event.IsChannelEvent())
		return OptionalMessage::Empty();
	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	if (params.size() == 1) {
		if (event.get_fd() != this->get_fd())
			return OptionalMessage::Empty();
		std::vector<std::string> messages = channel.RequestModeInfo(*this);
		messages.insert(messages.begin(), channel.get_name());
		return OptionalMessage::Create(this->get_fd(),
				this->CreateReplyMessage(ResponseStatus::RPL_CHANNELMODEIS.get_code(), messages));
	}
	if (!channel.ContainsUser(*this))
		return OptionalMessage::Empty();
	const Mode mode = Mode::Analyze(params[1]);
	std::vector<std::string> messages;
	messages.push_back(channel.get_name());
	messages.push_back(mode.ToString());
	switch (mode.get_mode()) {
	case 'i':
	case 't':
		break ;
	case 'o':
		messages.push_back(params[2]);
		break ;
	case 'k':
		messages.push_back(params[2].substr(0, kKeyMaxLength));
		break ;
	case 'l':
		if (mode.is_plus()) {
			std::stringstream ss;
			ss << utils::Stoi(params[2]);
			messages.push_back(ss.str());
		}
		break ;
	default:
		break ;
	}
	return OptionalMessage::Create(this->get_fd(),
			event.get_executer().CreateCommonMessage(event.get_command(), messages));
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
			else {
				std::vector<std::string> params = event.get_command_params();
				context_message = utils::Join(params.begin(), params.end(), " "); 
			}
			return OptionalMessage::Create(this->fd_, prefix_message + context_message + utils::kNewLine);
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
	if (event.get_fd() != this->get_fd())
		return ;
	if (!this->user_name_.empty())
		event.set_error_status(ErrorStatus::ERR_ALREADYREGISTRED);
}

void User::CkJoinCommand(Event& event) const {
	if (event.get_fd() != this->get_fd())
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
	return ;
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

void User::CkModeCommand(Event& event) const {
	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() <= 1)
		return ;
	const Mode mode = Mode::Analyze(params[1]);
	if (mode.get_mode() == 'o' && params[2] == this->nick_name_)
		event.IncreaseUserCount();
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

int User::get_fd() const {
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

bool	User::IsVerified() const {
	if (!this->is_password_authenticated_
		|| this->nick_name_.empty()
		|| this->user_name_.empty()){
		return false;
	}
	return true;
}
