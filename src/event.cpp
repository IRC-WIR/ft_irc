#include "event.h"
#include "user.h"

const std::string Event::NoErrorException::kMessage = "there is no ErrorStatus.";
const std::string Event::NoExecuterException::kMessage = "there is no executer.";
const std::string Event::AlreadySetException::kMessage = "already exists executer.";

Event::Event(int fd, int event_type)
		: fd_(fd), event_type_(event_type), command_(&Command::kNotFound),
		error_status_(NULL), executer_(NULL), user_count_(0) {
	return ;
}

Event::Event(const Event& src)
		: fd_(src.get_fd()), event_type_(src.get_event_type()), command_(&src.get_command()),
		error_status_(src.error_status_), executer_(src.executer_), user_count_(src.get_user_count()) {
	this->set_command(src.get_command());
	this->set_command_params(src.get_command_params());
	this->set_do_nothing(src.is_do_nothing());
}

Event::~Event() {
	return ;
}

void Event::IncreaseUserCount() {
	this->user_count_++;
}

int Event::get_user_count() const {
	return this->user_count_;
}

int Event::get_fd() const {
	return fd_;
}

int Event::get_event_type() const {
	return event_type_;
}

const Command& Event::get_command() const {
	return *command_;
}

const std::vector<std::string>& Event::get_command_params() const {
	return command_params_;
}

const ErrorStatus& Event::get_error_status() const {
	if (!this->HasErrorOccurred())
		throw Event::NoErrorException();
	return *this->error_status_;
}

void Event::set_command(const Command& command) {
	this->command_ = &command;
}

void Event::set_command_params(const std::vector<std::string>& commmand_params) {
	command_params_.clear();
	for (std::vector<std::string>::const_iterator it = commmand_params.begin();
		it != commmand_params.end(); it ++) {
		command_params_.push_back(*it);
	}
}

void Event::set_error_status(const ErrorStatus& error_status) {
	this->error_status_ = &error_status;
}

bool Event::HasErrorOccurred() const {
	return (this->error_status_ != NULL);
}

bool Event::IsChannelEvent() const {
	return false;
}

void Event::set_executer(const User& user) {
	if (this->executer_ != NULL)
		throw Event::AlreadySetException();
	this->executer_ = &user;
}

const User& Event::get_executer() const {
	if (this->executer_ == NULL)
		throw Event::NoExecuterException();
	return *(this->executer_);
}

void Event::set_do_nothing(bool is_do_nothing) {
	this->is_do_nothing_ = is_do_nothing;
}

bool Event::is_do_nothing() const {
	if (!(this->get_command() == Command::kPass
			|| this->get_command() == Command::kNick
			|| this->get_command() == Command::kUser
			|| this->get_command() == Command::kQuit)) {
		try {
			if (!this->get_executer().IsVerified())
				return true;
		} catch (const Event::NoExecuterException& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	return !this->HasErrorOccurred() && this->is_do_nothing_;
}

// ERR_NOSUCHNICK, ERR_NOSUCHCHANNEL, 
std::string Event::CreateErrorMessage(const User& user, const std::string& target) const {
	const ErrorStatus& error_status = this->get_error_status();
	std::stringstream ss;
	//add hostname
	ss << ":";
	ss << utils::kHostName;
	ss << " ";
	//add error no
	ss << utils::FillZero(error_status.get_code(), 3);
	ss << " ";
	//add nick name
	ss << (user.get_nick_name().empty()? "*" : user.get_nick_name()) ;
	ss << " ";
	//add target
	ss << this->CreateTargetStr(target);
	//add Error Message
	ss << ":";
	ss << error_status.get_message();
	ss << utils::kNewLine;
	return ss.str();
}

std::string Event::CreateTargetStr(const std::string& target) const {
	const ErrorStatus& error_status = this->get_error_status();

	if (error_status == ErrorStatus::ERR_NOSUCHNICK
			|| error_status == ErrorStatus::ERR_NOSUCHCHANNEL
			|| error_status == ErrorStatus::ERR_TOOMANYCHANNELS
			|| error_status == ErrorStatus::ERR_ERRONEUSNICKNAME
			|| error_status == ErrorStatus::ERR_NICKNAMEINUSE
			|| error_status == ErrorStatus::ERR_UNKNOWNMODE
			|| error_status == ErrorStatus::ERR_WRONGMODEPARAMS)
		return (target + " "); // targetを設定してもらう
	else if (error_status == ErrorStatus::ERR_CANNOTSENDTOCHAN
			|| error_status == ErrorStatus::ERR_NOTONCHANNEL
			|| error_status == ErrorStatus::ERR_KEYSET
			|| error_status == ErrorStatus::ERR_CHANNELISFULL
			|| error_status == ErrorStatus::ERR_INVITEONLYCHAN
			|| error_status == ErrorStatus::ERR_BADCHANNELKEY
			|| error_status == ErrorStatus::ERR_CHANOPRIVSNEEDED)
		return (target + " "); // しっかりChannelEventにしておけばtarget不要
	else if (error_status == ErrorStatus::ERR_USERNOTINCHANNEL
			|| error_status == ErrorStatus::ERR_USERONCHANNEL)
		return (target + " "); // しっかりChannelEventにしたうえでtaretも設定する
	else if (error_status == ErrorStatus::ERR_NEEDMOREPARAMS)
		return (this->get_command().get_name() + " ");
	else
		return "";
	/*
	else に当たるもの
	ERR_NOTEXTTOSEND
	ERR_NONICKNAMEGIVEN
	ERR_ALREADYREGISTRED
	ERR_PASSWDMISMATCH
	*/
}

Event::NoErrorException::NoErrorException()
		: std::runtime_error(Event::NoErrorException::kMessage) {
	return ;
}

Event::NoExecuterException::NoExecuterException()
		: std::runtime_error(Event::NoExecuterException::kMessage) {
	return ;
}

Event::AlreadySetException::AlreadySetException()
		: std::runtime_error(Event::AlreadySetException::kMessage) {
	return ;
}