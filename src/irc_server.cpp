#include "irc_server.h"

IrcServer::IrcServer()
{
	return ;
}

IrcServer::IrcServer(std::string port, std::string password)
{
	

	if (ValidPort(port) || ValidPassword(password))
		exit 1;

	this->password_ = validPassword;
	this->port_no_ = validPort;
}

//portのバリデーションチェック
bool IrcServer::ValidPort(std::string port)
{
	for (char entry : port)
	{
		if (!isdigit(entry))
			return true;
	}
	//1024~65535
	if (port.length() > 5)
		return true;
	int	port_int = atoi(port.c_str());
	if (port_int < 1024 || port_int > 65535)
		return true;
	return false;
}
bool IrcServer::ValidPassword(std::string input)
{
	

}