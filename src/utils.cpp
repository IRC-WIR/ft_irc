#include "utils.h"


namespace utils{

void check_digital_str(std::string num_str)
{
	for (int i = 0; i < (int)num_str.length(); i++)
	{
		if (!isdigit(num_str[i]))
		{
			//数字で構成されていない例外を投げる
			throw (utilsException(kNotDigitalNumber));
		}
	};
}


int ft_stoi(std::string num_str)
{
	std::stringstream ss(num_str);
	int num_int;	ss >> num_int;
	return (num_int);
}

std::string ft_split_before(const std::string& str, const std::string& delim)
{
	std::string::size_type n = str.find(delim);
	if (n == std::string::npos)
		return "";
	return str.substr(0, n);
}

std::string ft_split_after(const std::string& str, const std::string& delim)
{
	std::string::size_type n = str.find(delim);
	if (n == std::string::npos)
		return "";
	return str.substr(n);
}

void print_string_vector(const std::vector<std::string>& str_vec)
{
	for (std::vector<std::string>::const_iterator it = str_vec.begin();
		it != str_vec.end();
		it ++)
	{
		std::cout << "size: " << it->size() << std::endl;
		std::cout << "\"" << *it << "\"" << std::endl;
	}
}

void erase_space(std::string& str)
{
	std::string::size_type pos;
	while((pos = str.find('\n')) != std::string::npos)
	{
		str.erase(pos, 1);
	}
}

utilsException::utilsException(const std::string& msg) : std::invalid_argument(msg) {};

}