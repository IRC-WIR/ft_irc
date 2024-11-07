#include "response_status.h"

const ResponseStatus

	ResponseStatus::RPL_WELCOME(001, "Welcome to the Internet Relay Network"),
	ResponseStatus::RPL_CHANNELMODEIS(324, ""),
	ResponseStatus::RPL_NOTOPIC(331, "No topic is set."),
	ResponseStatus::RPL_TOPIC(332, ""),
	ResponseStatus::RPL_NAMREPLY(353, ""),
	ResponseStatus::RPL_ENDOFNAMES(366, "End of /NAMES list")
	;

// 呼ばれない
ResponseStatus::ResponseStatus() : code_(0), message_("") {
	return ;
}

ResponseStatus::ResponseStatus(int code, const std::string& message) : code_(code), message_(message) {
	return ;
}

ResponseStatus::~ResponseStatus() {
	return ;
}

const std::string& ResponseStatus::get_message() const {
	return this->message_;
}

int ResponseStatus::get_code() const {
	return this->code_;
}

bool operator ==(const ResponseStatus& status1, const ResponseStatus& status2) {
	return (&status1 == &status2);
}

bool operator !=(const ResponseStatus& status1, const ResponseStatus& status2) {
	return !(status1 == status2);
}