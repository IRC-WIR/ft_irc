#ifndef ERROR_STATUS_H_
# define ERROR_STATUS_H_

# include <string>

class ErrorStatus {
    public:
        static const ErrorStatus
            kErrNeedMoreParams,
            kErrAlreadyRegistred
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

#endif