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
	void check_digital_str(std::string num_str);
	int	ft_stoi(std::string num_str);
	std::string ft_split_before(const std::string& str, const std::string& delim);
	std::string ft_split_after(const std::string& str, const std::string& delim);
	void erase_newline(std::string& str);
	void erase_space(std::string& str);
	bool is_ascii(char c);
	bool is_ascii_str(const std::string& str);
	void convert_to_upper(std::string& str);

	template <typename K, typename V>
	void mergeMaps(std::map<K, V>& dest_map, const std::map<K, V>& src_map)
	{
		for (typename std::map<K, V>::const_iterator it = src_map.begin();
			it != src_map.end(); it++)
		{
			dest_map.insert(*it);
		}
	}


	//debug
	void print_string_vector(const std::vector<std::string>& str_vec);

	//utils Exception
	class utilsException : public std::invalid_argument
	{
		public:
			utilsException(const std::string& msg);
	};

	//エラーメッセージ定数
	static const std::string kNotDigitalNumber = "Input Value is not digital number";
};

#endif

