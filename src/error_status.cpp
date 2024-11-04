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
	ErrorStatus::ERR_CHANNELISFULL(471, "Cannot join channel (+l)"),
	ErrorStatus::ERR_INVITEONLYCHAN(473, "Cannot join channel (+i)"),
	ErrorStatus::ERR_BADCHANNELKEY(475, "Cannot join channel (+k)")
	;

ErrorStatus::ErrorStatus() : ResponseStatus() {
}

ErrorStatus::ErrorStatus(int code, const std::string& message) : ResponseStatus(code, message) {
}

ErrorStatus::~ErrorStatus() {
}