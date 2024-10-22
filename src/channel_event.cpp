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