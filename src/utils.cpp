#include "utils.h"

int utils::ft_stoi(std::string num_str)
{
	for (int i = 0; i < (int)num_str.length(); i++)
	{
		if (!isdigit(num_str[i]))
		{
			//数字で構成されていない例外を投げる
			//throw (IrcException(kPortErrMsg));
		}
	}
	std::stringstream ss(num_str);
	int num_int;	ss >> num_int;
	return (num_int);
}

std::string utils::ft_split_before(const std::string& str, const std::string& delim)
{
	std::string::size_type n = str.find(delim);
	if (n == std::string::npos)
		return "";
	return str.substr(0, n);
}

std::string utils::ft_split_after(const std::string& str, const std::string& delim)
{
	std::string::size_type n = str.find(delim);
	if (n == std::string::npos)
		return "";
	return str.substr(n);
}

void utils::print_string_vector(const std::vector<std::string>& str_vec)
{
	for (std::vector<std::string>::const_iterator it = str_vec.begin();
		it != str_vec.end();
		it ++)
	{
		std::cout << "size: " << it->size() << std::endl;
		std::cout << "\"" << *it << "\"" << std::endl;
	}
}

void utils::erase_space(std::string& str)
{
	std::string::size_type pos;
	while((pos = str.find('\n')) != std::string::npos)
	{
		str.erase(pos, 1);
	}
}