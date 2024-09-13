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