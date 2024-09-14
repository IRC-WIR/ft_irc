#ifndef IRC_SERVER_H_
 #define IRC_SERVER_H_

#include "event_handler.h"
#include "event_listener.h"
#include "user.h"
#include "channel.h"
#include "start_event_listener.h"
#include "end_event_listener.h"
#include "utils.h"


class IrcServer{
	public:
		IrcServer();
		~IrcServer();

		void	Run();

		std::string		get_password();
		void			set_password(std::string password);
		std::string		get_port_no();
		void			set_port_no(std::string port_no);
		std::vector<Channel>	get_channels();
		std::vector<User>	get_users();
		void	add_channel(Channel *channel);
		void	remove_channel(std::string name);
		void	add_user(User *user);
		void	remove_user(std::string nickname);
		void	set_event_handler(EventHandler event_handler);
		//例外処理のネストクラス
		class IrcException : public std::exception
		{
			public:
				IrcException(std::string msg);
				~IrcException() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;;
				const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;

			private:
				std::string msg_;
		};


	private:
		std::vector<User*>	users_;
		std::vector<Channel*>	channels_;
		EventListener*	start_event_listener_;
		EventListener*	end_event_listener_;
		EventHandler	event_handler_;
		std::string	password_;
		std::string	port_no_;

		//エラーメッセージ定数
		static const std::string kPortErrMsg;
		static const std::string kPasswordErrMsg;
};

#endif
