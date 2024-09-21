#include "irc_server.h"

const std::string IrcServer::kPortErrMsg = "Input the port number between 1024~65535";
const std::string IrcServer::kPasswordErrMsg = "Input the password in printable ASCII code 33~126 and at least 8 characters";

IrcServer::IrcServer()
{
	return ;
}

IrcServer::~IrcServer()
{
	return ;
}

void	IrcServer::Run()
{
	while (1)
	{
		event_handler_.ExecutePoll();
		event_handler_.WaitMillSecond(800);
		//debug
		for (std::vector<User*>::iterator it = users_.begin();
			it != users_.end(); it++)
		{
			std::cout << "user fd: " << (*it)->get_fd() << std::endl;
			std::cout << "user is_password_authenticated: " << (*it)->get_is_password_authenticated() << std::endl;
		}
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
	for (int i = 0; i < (int)port_no.length(); i++)
	{
		if (!isdigit(port_no[i]))
			throw (IrcException(kPortErrMsg));
	}
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

void	IrcServer::set_event_handler(EventHandler event_handler)
{
	event_handler_ = event_handler;
}

void	IrcServer::add_channel(Channel *channel)
{
	channels_.push_back(channel);
}


void	IrcServer::add_user(User *user)
{
	user->set_server_password(password_);
	users_.push_back(user);
}

std::vector<User*>	IrcServer::get_users(){
	return users_;
}

//IrcServerの例外処理
IrcServer::IrcException::IrcException(const std::string& msg) : std::invalid_argument(msg) {};