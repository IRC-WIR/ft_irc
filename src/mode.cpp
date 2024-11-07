#include "mode.h"
#include <sstream>

const std::string Mode::kSigns = "+-";
const std::string::size_type Mode::kPlusPos = Mode::kSigns.find('+');

Mode Mode::Analyze(const std::string& input) {
	bool is_plus = true;
	char mode = '\0';
	for (std::string::size_type i = 0; i < input.length(); i++) {
		std::string::size_type pos = Mode::kSigns.find(input[i]);
		if (pos != std::string::npos) {
			is_plus = (pos == Mode::kPlusPos);
			continue ;
		}
		mode = input[i];
		break ;
	}
	return Mode(mode, is_plus);
}

Mode::Mode() : mode_('\0'), is_plus_(false) {
}

Mode::Mode(char mode, bool is_plus) : mode_(mode), is_plus_(is_plus) {
}

Mode::Mode(const Mode& src) : mode_(src.get_mode()), is_plus_(src.is_plus()) {
}

Mode::~Mode() {
}

char Mode::get_mode() const {
	return this->mode_;
}

bool Mode::is_plus() const {
	return this->is_plus_;
}

std::string Mode::ToString() const {
	std::stringstream ss;
	if (this->is_plus())
		ss << "+";
	else
		ss << "-";
	ss << this->get_mode();
	return ss.str();
}