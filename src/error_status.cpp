#include "error_status.h"

const ErrorStatus
    ErrorStatus::kError = ErrorStatus(404, "Not Found"),
    ErrorStatus::kError2 = ErrorStatus(404, "Not Found"),
    ErrorStatus::kError3 = ErrorStatus(404, "Not Found"),
    ErrorStatus::kError4 = ErrorStatus(404, "Not Found"),
    ErrorStatus::kError5 = ErrorStatus(404, "Not Found");

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