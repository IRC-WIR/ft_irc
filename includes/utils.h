#ifndef UTILS_H_
 #define UTILS_H_

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring> //for std::memset
#include <utility> //for std::pair

namespace utils {
	void check_digital_str(std::string num_str);
	int	ft_stoi(std::string num_str);
	std::string ft_split_before(const std::string& str, const std::string& delim);
	std::string ft_split_after(const std::string& str, const std::string& delim);
	//debug
	void print_string_vector(const std::vector<std::string>& str_vec);
	bool is_same_string(const std::string& dest, const std::string& src);
	//int count_space(const std::string& str);
	void erase_space(std::string& str);

	class utilsException : public std::invalid_argument
	{
		public:
			utilsException(const std::string& msg);
	};
	//エラーメッセージ定数
	static const std::string kNotDigitalNumber = "Input Value is not digital number";
};

#endif

