#include "channel.h"
#include "channel_event.h"
#include "utils.h"
#include "mode.h"
#include <algorithm>

const std::string Channel::kHandlingModes = "itkol";

template <typename T, typename U>
const std::string Channel::MyMap<T, U>::kErrMsg("not found the key");

static const User* SearchByNick(const utils::MyVector<const User*>& vector, const std::string& nick_name) {
	for (utils::MyVector<const User*>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
		if (utils::StrToLower((*it)->get_nick_name()) == utils::StrToLower(nick_name))
			return *it;
	}
	return NULL;
}

static const User* SearchByFD(const utils::MyVector<const User*>& vector, int fd) {
	for (utils::MyVector<const User*>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
		if ((*it)->get_fd() == fd)
			return *it;
	}
	return NULL;
}

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
	// tモードはデフォルトでtrueっぽい
	this->mode_map_['t'] = true;
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

bool Channel::IsMode(const char& c) const{
	return mode_map_(c);
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

std::vector<std::string> Channel::RequestModeInfo(const User& client) const {
	std::vector<std::string> ret;
	for (std::string::size_type i = 0; i < Channel::kHandlingModes.length(); i++) {
		if (Channel::kHandlingModes[i] == 'o')
			continue ;
		if (this->mode_map_(Channel::kHandlingModes[i])) {
			if (ret.empty())
				ret.push_back("+");
			ret[0] += Channel::kHandlingModes[i];
			if (Channel::kHandlingModes[i] == 'k') {
				if (this->ContainsUser(client))
					ret.push_back(this->key_);
				else
					ret.push_back("<key>");
			} else if (Channel::kHandlingModes[i] == 'l') {
				std::stringstream ss;
				ss << this->max_member_num_;
				ret.push_back(ss.str());
			}
		}
	}
	return ret;
}

void Channel::CheckCommand(Event*& event) const {
	const Command& command = event->get_command();

	if (command == Command::kPass)
		CkPassCommand(*event);
	else if (command == Command::kNick)
		CkNickCommand(*event);
	else if (command == Command::kUser)
		CkUserCommand(*event);
	else if (command == Command::kJoin)
		CkJoinCommand(event);
	else if (command == Command::kInvite)
		CkInviteCommand(event);
	else if (command == Command::kKick)
		CkKickCommand(*event);
	else if (command == Command::kTopic)
		CkTopicCommand(event);
	else if (command == Command::kMode)
		CkModeCommand(event);
	else if (command == Command::kPrivmsg)
		CkPrivmsgCommand(event);
	else if (command == Command::kQuit)
		CkQuitCommand(*event);
}

OptionalMessage Channel::ExecuteCommand(const Event& event) {
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
	if (!event.IsChannelEvent())
		return OptionalMessage::Empty();
	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	if (this == &channel) {
		std::vector<std::string> params = event.get_command_params();
		if (params.size() > 1)
			this->set_topic(utils::Join(params.begin() + 1, params.end(), " "));
	}
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExModeCommand(const Event& event) {
	const int kKeyMaxLength = 32;

	if (event.HasErrorOccurred()
			|| !event.IsChannelEvent())
		return OptionalMessage::Empty();

	const Channel& channel = dynamic_cast<const ChannelEvent&>(event).get_channel();
	if (this != &channel)
		return OptionalMessage::Empty();
	const std::vector<std::string>& params = event.get_command_params();
	if (params.size() <= 1)
		return OptionalMessage::Empty();
	const Mode mode = Mode::Analyze(params[1]);
	if (mode.get_mode() != 'o')
		this->mode_map_[mode.get_mode()] = mode.is_plus();
	switch (mode.get_mode()) {
	case 'i':
	case 't':
		break ;
	case 'k':
		if (mode.is_plus())
			this->key_ = params[2].substr(0, kKeyMaxLength);
		else
			this->key_.clear();
		break ;
	case 'l':
		if (mode.is_plus())
			this->max_member_num_ = utils::Stoi(params[2]);
		else
			this->max_member_num_ = 0;
		break ;
	case 'o':
		if (mode.is_plus())
			this->GiveOperator(*SearchByNick(this->members_, params[2]));
		else
			this->TakeOperator(*SearchByNick(this->operators_, params[2]));
		break ;
	default:
		break ;
	}
	return OptionalMessage::Empty();
}

OptionalMessage Channel::ExPrivmsgCommand(const Event& event) {
	(void)event;
	return OptionalMessage::Empty();
}
OptionalMessage Channel::ExQuitCommand(const Event& event){

	RemoveUser(event.get_executer());
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
	const std::vector<std::string>& params = event->get_command_params();
	if (utils::StrToLower(params[0]) != utils::StrToLower(this->name_))
		return ;

	ChannelEvent* channel_event = new ChannelEvent(*event, *this);
	delete event;
	event = channel_event;
	if (SearchByFD(this->operators_, event->get_fd()) != NULL
			|| SearchByFD(this->members_, event->get_fd()) != NULL) {
		event->set_do_nothing(true);
		return ;
	}
	const std::string key = params.size() >= 2 ? params[1] : "";
	if (this->mode_map_('k') && this->key_ != key)
		event->set_error_status(ErrorStatus::ERR_BADCHANNELKEY);
	else if (this->mode_map_('i'))
		event->set_error_status(ErrorStatus::ERR_INVITEONLYCHAN);
	else if (this->mode_map_('l') && this->operators_.size() + this->members_.size() >= this->max_member_num_)
		event->set_error_status(ErrorStatus::ERR_CHANNELISFULL);
}

void Channel::CkInviteCommand(Event*& event) const {
	const std::vector<std::string> params = event->get_command_params();
	if (params.size() < 2)
		return ;
	if (utils::StrToLower(params[1]) != utils::StrToLower(this->name_))
		return ;

	ChannelEvent* channel_event = new ChannelEvent(*event, *this);
	delete event;
	event = channel_event;
	if (SearchByFD(this->operators_, event->get_fd()) == NULL) {
		if (SearchByFD(this->members_, event->get_fd()) == NULL)
			event->set_error_status(ErrorStatus::ERR_NOTONCHANNEL);
		else
			event->set_error_status(ErrorStatus::ERR_CHANOPRIVSNEEDED);
		return ;
	}
	if (this->ContainsUserByNick(params[0])) {
		event->set_error_status(ErrorStatus::ERR_USERONCHANNEL);
		return ;
	}
}

void Channel::CkKickCommand(Event& event) const {
	(void)event;
	std::cout << "Check Kick called!" << std::endl;
	utils::PrintStringVector(event.get_command_params());
}

void Channel::CkTopicCommand(Event*& event) const {
	const std::vector<std::string> params = event->get_command_params();
	if (utils::StrToLower(params[0]) != utils::StrToLower(this->name_))
		return ;
	ChannelEvent* channel_event = new ChannelEvent(*event, *this);
	delete event;
	event = channel_event;
	if (SearchByFD(operators_, event->get_fd()) == NULL && SearchByFD(members_, event->get_fd()) == NULL) {
		event->set_error_status(ErrorStatus::ERR_NOTONCHANNEL);
		return ;
	}
	if (this->mode_map_('t') && SearchByFD(operators_, event->get_fd()) == NULL) {
		event->set_error_status(ErrorStatus::ERR_CHANOPRIVSNEEDED);
		return ;
	}
}

void Channel::CkPrivmsgCommand(Event*& event) const {
	if (event->get_command_params()[0] != this->get_name())
		return ;
	//チャンネルイベントを作成する
	ChannelEvent* channel_event = new ChannelEvent(*event, *this);
	delete event;
	event = channel_event;
	//チームメンバーか否か
	if (SearchByFD(this->members_, event->get_fd()) == NULL && SearchByFD(this->operators_, event->get_fd()) == NULL) {
		event->set_error_status(ErrorStatus::ERR_CANNOTSENDTOCHAN);
		return ;
	}
}

void Channel::CkModeCommand(Event*& event) const {
	const std::vector<std::string>& params = event->get_command_params();
	if (utils::StrToLower(params[0]) != utils::StrToLower(this->name_))
		return ;

	ChannelEvent* channel_event = new ChannelEvent(*event, *this);
	delete event;
	event = channel_event;

	if (params.size() <= 1)
		return ;
	if (SearchByFD(this->operators_, event->get_fd()) == NULL) {
		event->set_error_status(ErrorStatus::ERR_CHANOPRIVSNEEDED);
		return ;
	}
	const Mode mode = Mode::Analyze(params[1]);
	switch (mode.get_mode()) {
	case 'i':
	case 't':
		if (mode.is_plus() == this->mode_map_(mode.get_mode()))
			event->set_do_nothing(true);
		break ;
	case 'k':
		if (mode.is_plus() == this->mode_map_(mode.get_mode()))
			event->set_do_nothing(true);
		else if (!mode.is_plus() && params[2] != this->key_) {
			event->set_error_status(ErrorStatus::ERR_KEYSET);
			return ;
		}
		break ;
	case 'o':
		if (!this->ContainsUserByNick(params[2]))
			break ;
		if (SearchByNick(this->operators_, params[2]) != NULL) {
			if (mode.is_plus())
				event->set_do_nothing(true);
		} else if (!mode.is_plus())
			event->set_do_nothing(true);
		break ;
	case 'l':
		if (!mode.is_plus() && !this->mode_map_(mode.get_mode()))
			event->set_do_nothing(true);
		break ;
	default:
		break ;
	}
}

void Channel::CkQuitCommand(Event& event) const {
	(void)event;
	return ;
}