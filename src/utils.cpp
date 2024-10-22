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
	return str.substr(n + delim.size());
}

void print_string_vector(const std::vector<std::string>& str_vec)
{
	int i = 0;
	for (std::vector<std::string>::const_iterator it = str_vec.begin();
		it != str_vec.end();
		it ++)
	{
		std::cout << "i: " << i << ", size: " << it->size();
		std::cout << ", \"" << *it << "\"" << std::endl;
		i ++;
	}
}

void erase_newline(std::string& str)
{
	std::string::size_type pos;
	while ((pos = str.find("\r\n")) != std::string::npos)
		str.erase(pos, 2);
	while((pos = str.find('\n')) != std::string::npos)
		str.erase(pos, 1);
}

void erase_space(std::string& str)
{
	std::string::size_type pos;
	while ((pos = str.find(" ")) != std::string::npos)
		str.erase(pos, 1);
}

bool is_ascii(char c)
{
	return static_cast<unsigned char>(c) <= 127;
}

bool is_ascii_str(const std::string& str)
{
	std::string::const_iterator it = str.begin();
	while (it != str.end())
	{
		if (!is_ascii(*it))
			return false;
		it ++;
	}

	return true;
}

void convert_to_upper(std::string& str)
{
	std::string::iterator it = str.begin();
	while (it != str.end())
	{
		if ('a' <= *it && *it <= 'z')
			*it = (*it) - ('a' - 'A');
		it ++;
	}
}

bool has_newlines(const std::string& str)
{
	std::string::size_type find_n_type;
	std::string::size_type find_r_n_type;
	find_n_type = str.find("\n");
	find_r_n_type = str.find("\r\n");

	if (find_n_type == std::string::npos && find_r_n_type == std::string::npos)
		return false;
	return true;
}

utilsException::utilsException(const std::string& msg) : std::invalid_argument(msg) {};


}
