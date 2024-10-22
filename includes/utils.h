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
	void CheckDigitalStr(std::string num_str);
	int	Stoi(std::string num_str);
	std::string SplitBefore(const std::string& str, const std::string& delim);
	std::string SplitAfter(const std::string& str, const std::string& delim);
	void EraseNewline(std::string& str);
	void EraseSpace(std::string& str);
	bool IsAscii(char c);
	bool IsAsciiStr(const std::string& str);
	void ConvertToUpper(std::string& str);
	bool HasNewlines(const std::string& str);

	//debug
	void PrintStringVector(const std::vector<std::string>& str_vec);

	//utils Exception
	class UtilsException : public std::invalid_argument
	{
		public:
			UtilsException(const std::string& msg);
	};

	//エラーメッセージ定数
	static const std::string kNotDigitalNumber = "Input Value is not digital number";
};

#endif

