#include "channel_event.h"

ChannelEvent::ChannelEvent(const Event& parent, const Channel& channel)
		: Event(parent), channel_(channel) {
	return ;
}

ChannelEvent::~ChannelEvent() {
	return ;
}

const Channel& ChannelEvent::get_channel() const {
	return this->channel_;
}

bool ChannelEvent::IsChannelEvent() const {
	return true;
}

std::string ChannelEvent::CreateTargetStr(const std::string& target) const {
	const ErrorStatus& error_status = this->get_error_status();

	if (error_status == ErrorStatus::ERR_CANNOTSENDTOCHAN
			|| error_status == ErrorStatus::ERR_TOOMANYCHANNELS
			|| error_status == ErrorStatus::ERR_NOTONCHANNEL
			|| error_status == ErrorStatus::ERR_KEYSET
			|| error_status == ErrorStatus::ERR_CHANNELISFULL
			|| error_status == ErrorStatus::ERR_INVITEONLYCHAN
			|| error_status == ErrorStatus::ERR_BADCHANNELKEY
			|| error_status == ErrorStatus::ERR_CHANOPRIVSNEEDED)
		return (this->get_channel().get_name() + " ");
	else if (error_status == ErrorStatus::ERR_USERNOTINCHANNEL
			|| error_status == ErrorStatus::ERR_USERONCHANNEL)
		return (target + " " + this->get_channel().get_name() + " ");
	else
		return Event::CreateTargetStr(target);
}