#include "error_status.h"

const ErrorStatus
    ErrorStatus::kErrNeedMoreParams = ErrorStatus(461, "Not enough parameters."),
    ErrorStatus::kErrAlreadyRegistred = ErrorStatus(462, "You may not reregister.")
    ;

// 呼ばれない
ErrorStatus::ErrorStatus() : code_(0), message_("")
{
    return ;
}

ErrorStatus::ErrorStatus(int code, const std::string& message) : code_(code), message_(message)
{
    return ;
}

ErrorStatus::~ErrorStatus()
{
    return ;
}

const std::string& ErrorStatus::get_error_message() const
{
    return this->message_;
}

int ErrorStatus::get_error_code() const
{
    return this->code_;
}