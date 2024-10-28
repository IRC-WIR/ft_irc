#include "optional_message.h"

const std::string OptionalMessage::EmptyMessageException::kErrorMessage("failed making pair: empty message");
const std::string OptionalMessage::kFilePath("../conf/ircserv.motd");

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
		: is_empty_(src.IsEmpty()), fd_(src.fd_), message_(src.message_) {
}

OptionalMessage::~OptionalMessage() {
}

bool OptionalMessage::IsEmpty() const {
	return this->is_empty_;
}

std::pair<int, std::string> OptionalMessage::MakePair() const {
	if (this->IsEmpty())
		throw OptionalMessage::EmptyMessageException();
	return std::make_pair(this->fd_, this->message_);
}

OptionalMessage OptionalMessage::AndThen(bool b){
	if (!b)
		return Empty();

	std::fstream s{kFilePath, s.binary | s.trunc | s.out};
	if (!s.is_open()) {
		std::cerr << "Could not open file : " << kFilePath << std::endl;
		return Empty();
	}
	std::string ret_message;
	for (std::string line; std::getline(s, line); ) {
		ret_message += line;
	}
	return Create(fd_, ret_message);
}


OptionalMessage::EmptyMessageException::EmptyMessageException()
		: std::runtime_error(OptionalMessage::EmptyMessageException::kErrorMessage) {
}