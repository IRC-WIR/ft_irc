#ifndef UTILS_H_
 #define UTILS_H_


#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace utils{

	int	ft_stoi(std::string num_str);
	std::string ft_split_before(const std::string& str, const std::string& delim);
	std::string ft_split_after(const std::string& str, const std::string& delim);
};

#endif

