#ifndef ERROR_STATUS_H_
 #define ERROR_STATUS_H_

#include "response_status.h"

class ErrorStatus : public ResponseStatus {
    public:
        static const ErrorStatus
            RPL_NOTOPIC,
            RPL_TOPIC,
            ERR_NOSUCHNICK,
            ERR_NOSUCHCHANNEL,
            ERR_CANNOTSENDTOCHAN,
            ERR_TOOMANYCHANNELS,
            ERR_NOTEXTTOSEND,
            ERR_NONICKNAMEGIVEN,
            ERR_ERRONEUSNICKNAME,
            ERR_NICKNAMEINUSE,
            ERR_NOTONCHANNEL,
            ERR_NEEDMOREPARAMS,
            ERR_ALREADYREGISTRED,
            ERR_PASSWDMISMATCH,
			ERR_CHANNELISFULL,
			ERR_INVITEONLYCHAN,
			ERR_BADCHANNELKEY,
            ERR_CHANOPRIVSNEEDED
            ;

	private:
		ErrorStatus(void);
		ErrorStatus(int, const std::string&);
		~ErrorStatus();

};

#endif