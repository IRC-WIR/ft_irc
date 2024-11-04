#include "response_status.h"

const ResponseStatus

	ResponseStatus::RPL_WELCOME(101, "Welcome to the Internet Relay Network")
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

const std::string& ResponseStatus::get_response_message() const {
    return this->message_;
}

int ResponseStatus::get_response_code() const {
    return this->code_;
}

bool operator ==(const ResponseStatus& status1, const ResponseStatus& status2) {
    return (&status1 == &status2);
}

bool operator !=(const ResponseStatus& status1, const ResponseStatus& status2) {
    return !(status1 == status2);
}