#include "channel.h"
#include "channel_event.h"
#include "utils.h"
#include <algorithm>

template <typename T, typename U>
const std::string Channel::MyMap<T, U>::kErrMsg("not found the key");

Channel::Channel(const User& op, const std::string& name)
		: name_(name) {
	this->operators_.push_back(&op);
	this->InitModeMap();
}

Channel::~Channel() {
	return ;
}

void Channel::InitModeMap() {
	this->mode_map_.clear();
	this->mode_map_['i'] = false;
	this->mode_map_['t'] = false;
	this->mode_map_['k'] = false;
	this->mode_map_['l'] = false;
}

void Channel::AddUser(const User& user) {
	this->members_.push_back(&user);
}

bool Channel::RemoveUser(const User& user) {
	if (this->operators_.Contains(&user)) {
		this->operators_.Remove(&user);
		return true;
	} else if (this->members_.Contains(&user)) {
		this->members_.Remove(&user);
		return true;
	}
	return false;
}

static const User* SearchByNick(const utils::MyVector<const User*>& vector, const std::string& nick_name) {
	for (utils::MyVector<const User*>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
		if (utils::StrToLower((*it)->get_nick_name()) == utils::StrToLower(nick_name))
			return *it;
	}
	return NULL;
}

bool Channel::RemoveUserByNick(const std::string& nick_name) {
	const User* user_ptr = SearchByNick(this->operators_, nick_name);
	if (user_ptr != NULL) {
		this->operators_.Remove(user_ptr);
		return true;
	}
	user_ptr = SearchByNick(this->members_, nick_name);
	if (user_ptr != NULL) {
		this->members_.Remove(user_ptr);
		return true;
	}
	return false;
}

bool Channel::ContainsUser(const User& user) const {
	return this->operators_.Contains(&user) || this->members_.Contains(&user);
}

bool Channel::ContainsUserByNick(const std::string& nick_name) const {
	return (SearchByNick(this->operators_, nick_name) != NULL || SearchByNick(this->members_, nick_name) != NULL);
}

bool Channel::GiveOperator(const User& user) {
	if (this->members_.Contains(&user)) {
		this->members_.Remove(&user);
		this->operators_.push_back(&user);
		return true;
	}
	return false;
}

bool Channel::TakeOperator(const User& user) {
	if (this->operators_.Contains(&user)) {
		this->operators_.Remove(&user);
		this->members_.push_back(&user);
		return true;
	}
	return false;
}

bool Channel::IsOperator(const User& user) const {
	return this->operators_.Contains(&user);
}

void Channel::set_topic(const std::string& topic) {
	this->topic_ = topic;
}

const std::string& Channel::get_topic() const {
	return this->topic_;
}

const std::string& Channel::get_name() const {
	return this->name_;
}

std::string Channel::GenerateMemberListWithNewUser(const User& new_user) const {
	std::string ret = this->GenerateMemberList();
	if (this->ContainsUser(new_user))
		return ret;
	else
		return ret + " " + new_user.get_nick_name();
}

std::string Channel::GenerateMemberList() const {
	std::stringstream ss;
	for (std::size_t i = 0; i < this->operators_.size(); i++) {
		if (i != 0)
			ss << " ";
		ss << "@" << this->operators_[i]->get_nick_name();
	}
	for (std::size_t i = 0; i < this->members_.size(); i++) {
		if (!this->operators_.empty() || i != 0)
			ss << " ";
		ss << this->members_[i]->get_nick_name();
	}
	return ss.str();
}

void Channel::CheckCommand(Event*& event) const {
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
			CkJoinCommand(event);
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
	return this->operators_.empty() && this->members_.empty();
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
	if (event.HasErrorOccurred()
			|| !event.IsChannelEvent())
		return OptionalMessage::Empty();

	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	if (this == &channel && !this->ContainsUser(event.get_executer()))
		this->AddUser(event.get_executer());
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

void Channel::CkJoinCommand(Event*& event) const {
	if (event->HasErrorOccurred())
		return ;
	const std::vector<std::string> params = event->get_command_params();
	if (utils::StrToLower(params[0]) != utils::StrToLower(this->name_))
		return ;

	ChannelEvent* channel_event = new ChannelEvent(*event, *this);
	delete event;
	event = channel_event;
	const std::string key = params.size() >= 2 ? params[1] : "";
	if (this->mode_map_('k') && this->key_ != key)
		event->set_res_status(ResponseStatus::ERR_BADCHANNELKEY);
	else if (this->mode_map_('i'))
		event->set_res_status(ResponseStatus::ERR_INVITEONLYCHAN);
	else if (this->mode_map_('l') && this->operators_.size() + this->members_.size() >= this->max_member_num_)
		event->set_res_status(ResponseStatus::ERR_CHANNELISFULL);
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
	(void)event;
	std::cout << "Check vmsg called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkModeCommand(Event& event) const {
	(void)event;
	std::cout << "Check Mode called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}
//check