#ifndef SERVER_H_
 #define SERVER_H_

#include "event_handler.h"

namespace server
{
	class IrcServer{
	public:
		IrcServer(EventHandler& event_handler);
		~IrcServer();
		void	Run();
		std::string		get_password();
		void			set_password(std::string password);
		std::string		get_port_no();
		void			set_port_no(std::string port_no);

	private:
		EventHandler&	event_handler_;
		std::string		password_;
		std::string		port_no_;

	};
	//例外処理
	class IrcException : public std::invalid_argument
	{
		public:
			IrcException(const std::string& msg);
	};
	//エラーメッセージ定数
	static const std::string kPortErrMsg = "Input the port number between 1024~65535";;
	static const std::string kPasswordErrMsg = "Input the password in printable ASCII code 33~126 and at least 8 characters";
}

#endif