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

namespace utils {
	void CheckPort(std::string port);
	void CheckPassword(std::string password);
	int	Stoi(std::string num_str);
	std::string SplitBefore(const std::string& str, const std::string& delim);
	std::string SplitAfter(const std::string& str, const std::string& delim);
	void EraseNewline(std::string& str);
	void EraseSpace(std::string& str);
	bool IsAscii(char c);
	bool IsAsciiStr(const std::string& str);
	void ConvertToUpper(std::string& str);
	bool HasNewlines(const std::string& str);
	bool HasDelimator(const std::string& str, const std::string& delim);

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
};

#endif

