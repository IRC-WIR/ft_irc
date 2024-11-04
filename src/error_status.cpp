#include "error_status.h"

const ErrorStatus
	ErrorStatus::ERR_NOSUCHCHANNEL(403, "No such channel"),
	ErrorStatus::ERR_TOOMANYCHANNELS(405, "You have joined too many channels"),
    ErrorStatus::ERR_NONICKNAMEGIVEN(431, "No nickname given"),
    ErrorStatus::ERR_ERRONEUSNICKNAME(432, "Erroneus nickname"),
    ErrorStatus::ERR_NICKNAMEINUSE(433, "Nickname is already in use"),
    ErrorStatus::ERR_NEEDMOREPARAMS(461, "Not enough parameters."),
    ErrorStatus::ERR_ALREADYREGISTRED(462, "You may not reregister."),
    ErrorStatus::ERR_PASSWDMISMATCH(464, "Password incorrect"),
	ErrorStatus::ERR_KEYSET(467, "Channel key already set"),
	ErrorStatus::ERR_CHANNELISFULL(471, "Cannot join channel (+l)"),
    ErrorStatus::ERR_UNKNOWNMODE(472, "is unknown mode char to me"),
	ErrorStatus::ERR_INVITEONLYCHAN(473, "Cannot join channel (+i)"),
	ErrorStatus::ERR_BADCHANNELKEY(475, "Cannot join channel (+k)"),
	ErrorStatus::ERR_WRONGMODEPARAMS(696, "Invalid mode parameter.")
    ;

// 呼ばれない
ErrorStatus::ErrorStatus() : code_(0), message_("") {
    return ;
}

ErrorStatus::ErrorStatus(int code, const std::string& message) : code_(code), message_(message) {
    return ;
}

ErrorStatus::~ErrorStatus() {
    return ;
}

const std::string& ErrorStatus::get_error_message() const {
    return this->message_;
}

int ErrorStatus::get_error_code() const {
    return this->code_;
}

bool operator ==(const ErrorStatus& status1, const ErrorStatus& status2) {
    return (&status1 == &status2);
}

bool operator !=(const ErrorStatus& status1, const ErrorStatus& status2) {
    return !(status1 == status2);
}