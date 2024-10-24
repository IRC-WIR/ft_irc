#include "error_status.h"

const ErrorStatus
    ErrorStatus::ERR_NEEDMOREPARAMS(461, "Not enough parameters."),
    ErrorStatus::ERR_ALREADYREGISTRED(462, "You may not reregister"),
    ErrorStatus::kError3(404, "Not Found"),
    ErrorStatus::kError4(404, "Not Found"),
    ErrorStatus::kError5(404, "Not Found");

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