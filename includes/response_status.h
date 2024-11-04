#ifndef RESPONSE_STATUS_H_
# define RESPONSE_STATUS_H_

# include <string>

class ResponseStatus {
    public:
        static const ResponseStatus
            RPL_WELCOME,
            RPL_NOTOPIC,
            RPL_TOPIC
            ;

        int get_response_code(void) const;
        const std::string& get_response_message(void) const;

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