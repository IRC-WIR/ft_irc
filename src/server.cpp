#include "server.h"

namespace Server {

IrcServer::IrcServer(EventHandler& event_handler) : event_handler_(event_handler)
{
}

IrcServer::~IrcServer()
{
}

void	IrcServer::Run()
{
	while (1)
	{
		event_handler_.ExecutePoll();
		event_handler_.WaitMillSecond(800);
	}
	return ;
}

std::string	IrcServer::get_password(){
	return password_;
}

void	IrcServer::set_password(std::string password)
{
	//printable ASCII code 33~126, at least 8 characters
	const char* input_chr_ptr = password.c_str();
	int i = 0;
	while (*input_chr_ptr)
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
	std::stringstream port_ss(port_no);
	int port_int;	port_ss >> port_int;
	//ポート番号は1024~65535の範囲
	if (port_int < 1024 || port_int > 65535)
		throw (IrcException(kPortErrMsg));
	port_no_ = port_no;
}

std::string	IrcServer::get_port_no(){
	return port_no_;
}

//IrcServerの例外処理
IrcException::IrcException(const std::string& msg) : std::invalid_argument(msg) {};

}
