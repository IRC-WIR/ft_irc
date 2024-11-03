#ifndef RESPONSE_STATUS_H_
# define RESPONSE_STATUS_H_

# include <string>

class ResponseStatus {
    public:
        static const ResponseStatus
            RPL_WELCOME,
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

        const std::string& get_error_message(void) const;
        int get_error_code(void) const;

    private:
        const int code_;
        const std::string message_;

        ResponseStatus(void);
        ResponseStatus(int, const std::string&);
        ~ResponseStatus();
};

bool operator ==(const ResponseStatus&, const ResponseStatus&);
bool operator !=(const ResponseStatus&, const ResponseStatus&);

#endif