#ifndef IRC_SERVER_H_
 #define IRC_SERVER_H_

#include "event_handler.h"
#include "event_listener.h"
#include "user.h"
#include "channel.h"
#include "start_event_listener.h"
#include "end_event_listener.h"
#include <sstream>

class StartEventListener;

class EndEventListener;

class IrcServer{
	public:
		IrcServer();
		~IrcServer();

		std::string	get_password();
		std::vector<Channel>	get_channels();
		std::vector<User>	get_users();
		void	add_channel(Channel channel);
		void	remove_channel(std::string name);
		void	add_user(User user);
		void	remove_user(std::string nickname);

		bool	ValidPort(std::string port);
		bool	ValidPassword(std::string password);
		void	set_password(std::string password);
		void	set_port_no(std::string port_no);
		void	set_event_handler(EventHandler event_handler);
		std::string	get_port_no();
		void	Run();

		//例外処理のネストクラス
//		class IrcException : public std::exception
//		{
//			public:
//				IrcException(std::string msg);
//				~IrcException();
//				const char* what() const noexcept;
//
//			private:
//				std::string msg_;
//		};


	private:
		std::vector<User>	users_;
		std::vector<Channel>	channels_;
		StartEventListener*	start_event_listener_;
		EndEventListener*	end_event_listener_;
		EventHandler	event_handler_;
		std::string	password_;
		std::string	port_no_;

		//エラーメッセージ定数
		static const std::string kPortErrMsg;
		static const std::string kPasswordErrMsg;
};

#endif
