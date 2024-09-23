#ifndef UTILS_H_
 #define UTILS_H_

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring> //for std::memset
#include <utility> //for std::pair

namespace utils{

	int	ft_stoi(std::string num_str);
	std::string ft_split_before(const std::string& str, const std::string& delim);
	std::string ft_split_after(const std::string& str, const std::string& delim);
	template <typename K, typename V>
	void mergeMaps(std::multimap<K, V>& dest_map, const std::map<K, V>& src_map)
	{
		for (typename std::map<K, V>::const_iterator it = src_map.begin();
			it != src_map.end(); it++)
		{
			dest_map.insert(*it);
		}
	}
	//debug
	void print_string_vector(const std::vector<std::string>& str_vec);
	bool is_same_string(const std::string& dest, const std::string& src);
	//int count_space(const std::string& str);
	void erase_space(std::string& str);

};

#endif

