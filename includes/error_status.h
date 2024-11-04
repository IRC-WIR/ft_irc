#ifndef ERROR_STATUS_H_
 #define ERROR_STATUS_H_

#include "response_status.h"

class ErrorStatus : public ResponseStatus {
	public:
		static const ErrorStatus
			ERR_NOSUCHCHANNEL,
			ERR_TOOMANYCHANNELS,
			ERR_NONICKNAMEGIVEN,
			ERR_ERRONEUSNICKNAME,
			ERR_NICKNAMEINUSE,
			ERR_NEEDMOREPARAMS,
			ERR_ALREADYREGISTRED,
			ERR_PASSWDMISMATCH,
			ERR_CHANNELISFULL,
			ERR_INVITEONLYCHAN,
			ERR_BADCHANNELKEY
			;

	private:
		ErrorStatus(void);
		ErrorStatus(int, const std::string&);

};

#endif