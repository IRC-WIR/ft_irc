#include "response_status.h"

const ResponseStatus

	ResponseStatus::RPL_WELCOME(101, "Welcome to the Internet Relay Network"),
	ResponseStatus::ERR_NOSUCHCHANNEL(403, "No such channel"),
	ResponseStatus::ERR_TOOMANYCHANNELS(405, "You have joined too many channels"),
    ResponseStatus::ERR_NONICKNAMEGIVEN(431, "No nickname given"),
    ResponseStatus::ERR_ERRONEUSNICKNAME(432, "Erroneus nickname"),
    ResponseStatus::ERR_NICKNAMEINUSE(433, "Nickname is already in use"),
    ResponseStatus::ERR_NEEDMOREPARAMS(461, "Not enough parameters."),
    ResponseStatus::ERR_ALREADYREGISTRED(462, "You may not reregister."),
    ResponseStatus::ERR_PASSWDMISMATCH(464, "Password incorrect"),
	ResponseStatus::ERR_CHANNELISFULL(471, "Cannot join channel (+l)"),
	ResponseStatus::ERR_INVITEONLYCHAN(473, "Cannot join channel (+i)"),
	ResponseStatus::ERR_BADCHANNELKEY(475, "Cannot join channel (+k)")
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

const std::string& ResponseStatus::get_error_message() const {
    return this->message_;
}

int ResponseStatus::get_error_code() const {
    return this->code_;
}

bool operator ==(const ResponseStatus& status1, const ResponseStatus& status2) {
    return (&status1 == &status2);
}

bool operator !=(const ResponseStatus& status1, const ResponseStatus& status2) {
    return !(status1 == status2);
}