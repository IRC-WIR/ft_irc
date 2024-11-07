#ifndef RESPONSE_STATUS_H_
# define RESPONSE_STATUS_H_

# include <string>

class ResponseStatus {
    public:
        static const ResponseStatus
            RPL_WELCOME,
            RPL_NOTOPIC,
            RPL_TOPIC,
            RPL_CHANNELMODEIS,
			RPL_INVITELIST,
			RPL_ENDOFINVITELIST,
			RPL_INVITING
            ;

        int get_code(void) const;
        const std::string& get_message(void) const;

    protected:
        ResponseStatus(void);
        ResponseStatus(int, const std::string&);
        virtual ~ResponseStatus();

    private:
        const int code_;
        const std::string message_;
};

bool operator ==(const ResponseStatus&, const ResponseStatus&);
bool operator !=(const ResponseStatus&, const ResponseStatus&);

#endif