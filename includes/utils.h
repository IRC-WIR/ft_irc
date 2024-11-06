#ifndef UTILS_H_
 #define UTILS_H_

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring> //for std::memset
#include <utility> //for std::pair
#include <set> //for std::set
#include <fstream> //for std::fstream
#include "optional_message.h"
#include <algorithm> // for std::find, std::copy
#include "response_status.h"
#include <ostream> // for std::ostringstream
#include <iterator> // for std::ostream_iterator

class User;

namespace utils {
	void CheckPort(std::string port);
	void CheckPassword(std::string password);
	int	Stoi(std::string num_str);
	std::string TrimBefore(const std::string& str, const std::string& delim);
	std::string TrimAfter(const std::string& str, const std::string& delim);
	void EraseNewline(std::string& str);
	void EraseSpace(std::string& str);
	bool IsAscii(char c);
	bool IsAsciiStr(const std::string& str);
	void ConvertToUpper(std::string& str);
	bool HasNewlines(const std::string& str);
	std::string GetWelcomeString(const ResponseStatus& res_status, const User& user);
	std::string StrToLower(const std::string& str);

	template <typename InputIterator>
	std::string Join(InputIterator begin, InputIterator end, const std::string& delim) {
		std::ostringstream os;
		std::copy(begin, end, std::ostream_iterator<std::string>(os, delim.c_str()));
		std::string ret = os.str();
		if (ret.find(ret.length() - delim.length()) != ret.npos)
			ret.erase(ret.length() - delim.length());
		return ret;
	}

	template <typename T>
	class MyVector : public std::vector<T> {
		public:
			bool Contains(const T& t) const {
				return (std::find(this->begin(), this->end(), t) != this->end());
			}
			bool Remove(const T& t) {
				typename MyVector<T>::iterator it = std::find(this->begin(), this->end(), t);
				if (it == this->end())
					return false;
				this->erase(it);
				return true;
			}
	};

	//debug
	void PrintStringVector(const std::vector<std::string>& str_vec);

	//utils Exception
	class UtilsException : public std::invalid_argument
	{
		public:
			UtilsException(const std::string& msg);
	};

	//エラーメッセージ定数
	static const std::string kNotDigitalNumber = "The input port is not digital number";
	static const std::string kNotPrintableAscii = "The input password is out of range of printable ASCII code 33~126";
	static const std::string kNotEnoughCharacters = "The input password is less than 8 characters";
	//FilePath
	static const std::string kFilePath = "./conf/ircserv.motd";
	//NewLine in IRC server
	static const std::string kNewLine = "\r\n";
	static std::string kHostName = "localhost";

};

#endif

