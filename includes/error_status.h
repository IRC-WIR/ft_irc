#ifndef ERROR_STATUS_H_
# define ERROR_STATUS_H_

# include <string>

class ErrorStatus {
    public:
        static const ErrorStatus
            ERR_NOSUCHNICK,
            ERR_CANNOTSENDTOCHAN,
            ERR_NOTEXTTOSEND,
            ERR_NONICKNAMEGIVEN,
            ERR_ERRONEUSNICKNAME,
            ERR_NICKNAMEINUSE,
            ERR_NEEDMOREPARAMS,
            ERR_ALREADYREGISTRED,
            ERR_PASSWDMISMATCH
            ;

        const std::string& get_error_message(void) const;
        int get_error_code(void) const;

    private:
        const int code_;
        const std::string message_;

        ErrorStatus(void);
        ErrorStatus(int, const std::string&);
        ~ErrorStatus();
};

bool operator ==(const ErrorStatus&, const ErrorStatus&);
bool operator !=(const ErrorStatus&, const ErrorStatus&);

#endif