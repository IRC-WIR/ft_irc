#include "error_status.h"

const ErrorStatus
    ErrorStatus::RPL_NOTOPIC(331, "No topic is set."),
    ErrorStatus::RPL_TOPIC(332, ""),
    ErrorStatus::ERR_NOSUCHNICK(401, "No such nick"),
    ErrorStatus::ERR_NOSUCHCHANNEL(403, "No such channel"),
    ErrorStatus::ERR_CANNOTSENDTOCHAN(404, "Cannot send to channel"),
    ErrorStatus::ERR_TOOMANYCHANNELS(405, "You have joined too many channels"),
    ErrorStatus::ERR_NOTEXTTOSEND(412, "No text to send"),
    ErrorStatus::ERR_NONICKNAMEGIVEN(431, "No nickname given"),
    ErrorStatus::ERR_ERRONEUSNICKNAME(432, "Erroneus nickname"),
    ErrorStatus::ERR_NICKNAMEINUSE(433, "Nickname is already in use"),
    ErrorStatus::ERR_NOTONCHANNEL(442, "You're not on that channel!"),
    ErrorStatus::ERR_NEEDMOREPARAMS(461, "Not enough parameters."),
    ErrorStatus::ERR_ALREADYREGISTRED(462, "You may not reregister."),
    ErrorStatus::ERR_PASSWDMISMATCH(464, "Password incorrect"),
	ErrorStatus::ERR_CHANNELISFULL(471, "Cannot join channel (+l)"),
	ErrorStatus::ERR_INVITEONLYCHAN(473, "Cannot join channel (+i)"),
	ErrorStatus::ERR_BADCHANNELKEY(475, "Cannot join channel (+k)"),
    ErrorStatus::ERR_CHANOPRIVSNEEDED(482, "You do not have access to change the topic on this channel")
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