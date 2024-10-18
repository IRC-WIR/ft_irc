#ifndef ERROR_STATUS
# define ERROR_STATUS

# include <string>

class ErrorStatus {
    public:
        static const ErrorStatus
            kError,
            kError2,
            kError3,
            kError4,
            kError5;

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