#ifndef CHANNEL_EVENT_H_
# define CHANNEL_EVENT_H_

# include "event.h"
# include "channel.h"

class ChannelEvent : public Event {
    public:
        ChannelEvent(const Event&, const Channel&);
        ~ChannelEvent();
        const Channel& get_channel(void) const;
		bool IsChannelEvent(void) const;

    private:
        const Channel& channel_;
};

#endif