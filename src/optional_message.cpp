#include "optional_message.h"

const std::string OptionalMessage::EmptyMessageException::kErrorMessage("failed making pair: empty message");

OptionalMessage OptionalMessage::Empty() {
	return OptionalMessage();
}

OptionalMessage OptionalMessage::Create(int fd, const std::string& message) {
	return OptionalMessage(fd, message);
}

OptionalMessage::OptionalMessage()
		: is_empty_(true), fd_(0), message_("") {
}

OptionalMessage::OptionalMessage(int fd, const std::string& message)
		: is_empty_(false), fd_(fd), message_(message) {
}

OptionalMessage::OptionalMessage(const OptionalMessage& src)
		: is_empty_(src.is_empty()), fd_(src.fd_), message_(src.message_) {
}

OptionalMessage::~OptionalMessage() {
}

bool OptionalMessage::is_empty() const {
	return this->is_empty_;
}

std::pair<int, std::string> OptionalMessage::MakePair() const {
	if (this->is_empty())
		throw OptionalMessage::EmptyMessageException();
	return std::pair(this->fd_, this->message_);
}

OptionalMessage::EmptyMessageException::EmptyMessageException()
		: std::runtime_error(OptionalMessage::EmptyMessageException::kErrorMessage) {
}