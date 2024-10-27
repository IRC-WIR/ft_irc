#include "channel.h"
#include <algorithm>

const std::string Channel::NoOperatorException::kErrorMessage("Channel has no operator");

Channel::Channel(const User& op, const std::string& name)
		: name_(name),  max_member_num_(10), operator_(&op) {
	return ;
}

Channel::~Channel() {
	return ;
}

void Channel::AddUser(const User& user) {
	this->users_.push_back(&user);
}

bool Channel::RemoveUser(const User& user) {
	std::vector<const User*>::iterator it = std::find(this->users_.begin(), this->users_.end(), &user);
	if (it == this->users_.end())
		return false;
	this->users_.erase(it);
	if (this->operator_ == &user) {
		if (this->users_.empty())
			this->operator_ = NULL;
		else
			this->operator_ = this->users_[0];
	}
	return true;
}

bool Channel::ContainsUser(const User& user) const {
	return std::find(this->users_.begin(), this->users_.end(), &user) != this->users_.end();
}

void Channel::set_operator(const User& user) {
	if (!this->ContainsUser(user))
		this->AddUser(user);
	this->operator_ = &user;
}

const User& Channel::get_operator() const {
	if (this->operator_ == NULL)
		throw Channel::NoOperatorException();
	return *this->operator_;
}

void Channel::set_topic(const std::string& topic) {
	this->topic_ = topic;
}

const std::string& Channel::get_topic() const {
	return this->topic_;
}

const std::string& Channel::get_name() const {
	return name_;
}



void Channel::set_key(const std::string& key) {
	this->key_ = key;
}

bool Channel::VerifyKey(const std::string& key) const {
	return (this->key_ == key);
}

void Channel::set_max_member_num(int num) {
	this->max_member_num_ = num;
}

void Channel::CheckCommand(Event& event) const {
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
			return;
	}
}

OptionalMessage Channel::ExecuteCommand(const Event& event) {
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

bool Channel::IsFinished() const {
	return this->users_.empty();
}

//Execute
OptionalMessage Channel::ExPassCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExNickCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExUserCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExJoinCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExInviteCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExKickCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExTopicCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExModeCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExPrivmsgCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}
//Execute

//Check
void Channel::CkPassCommand(Event& event) const {
	(void)event;
	std::cout << "Check Nick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkNickCommand(Event& event) const {
	(void)event;
	return ;
}

void Channel::CkUserCommand(Event& event) const {
	(void)event;
	return ;
}

void Channel::CkJoinCommand(Event& event) const {
	(void)event;
	std::cout << "Check Join called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkInviteCommand(Event& event) const {
	(void)event;
	std::cout << "Check vite called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkKickCommand(Event& event) const {
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkTopicCommand(Event& event) const {
	(void)event;
	std::cout << "Check opic called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkPrivmsgCommand(Event& event) const {
	const std::string& targe = event.get_command_params().front();
	if (targe == this->get_name())
	{
		event.erase_error_status();
		//channelイベントはどこに渡せる？
		ChannelEvent(event, *this);
	}
}

void Channel::CkModeCommand(Event& event) const {
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}
//check

Channel::NoOperatorException::NoOperatorException()
		: std::runtime_error(Channel::NoOperatorException::kErrorMessage) {
	return ;
}