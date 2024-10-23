#include "error_status.h"

const ErrorStatus
    ErrorStatus::ERR_NONICKNAMEGIVEN(431, " :No nickname given"),
    ErrorStatus::ERR_ERRONEUSNICKNAME(432, " :Erroneus nickname"),
    ErrorStatus::ERR_NICKNAMEINUSE(433, " :Nickname is already in use");

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