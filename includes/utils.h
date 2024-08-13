#ifndef UTILS_H_
 #define UTILS_H_

#include <string>
#include <sstream>

namespace utils{

	int	ft_stoi(std::string num_str)
	{
		for (char entry : num_str)
		{
			if (!isdigit(entry))
			{
				//数字で構成されていない例外を投げる
				//throw (IrcException(kPortErrMsg));
			}
		}
		std::stringstream ss(num_str);
		int num_int;	ss >> num_int;
		return (num_int);
	}

};

#endif
 
