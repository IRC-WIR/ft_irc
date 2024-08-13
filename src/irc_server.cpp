#include "irc_server.h"

const std::string IrcServer::kPortErrMsg = "Input the port number between 1024~65535";
const std::string IrcServer::kPasswordErrMsg = "Input the password in printable ASCII code 33~126 and at least 8 characters";

IrcServer::IrcServer()
{
	return ;
}

void	IrcServer::set_password(std::string password)
{
	//printable ASCII code 33~126, at least 8 characters
	const char* input_chr_ptr = password.c_str();
	int i = 0;
	while (!input_chr_ptr)
	{
		if (*input_chr_ptr < 33 || *input_chr_ptr > 126)
			throw(IrcException(kPasswordErrMsg));
		input_chr_ptr ++;
		i ++;
	}
	if (i < 8)
		throw(IrcException(kPasswordErrMsg));
	password_ = password;
}

void	IrcServer::set_port_no(std::string port_no)
{
	for (char entry : port_no)
	{
		if (!isdigit(entry))
			throw (IrcException(kPortErrMsg));
	}
	std::stringstream port_ss(port_no);
	int port_int;	port_ss >> port_int;
	//ポート番号は1024~65535の範囲
	if (port_int < 1024 || port_int > 65535)
		throw (IrcException(kPortErrMsg));
	port_no_ = port_no;
}

//IrcServerの例外処理
IrcServer::IrcException::IrcException(std::string msg) : msg_(msg) {}
IrcServer::IrcException::~IrcException() {}
const char* IrcServer::IrcException::what() const noexcept
{
	return msg_.c_str();
}