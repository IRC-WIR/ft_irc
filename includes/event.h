#ifndef EVENT_H_
	#define EVENT_H_

#include <stdexcept>
#include <string>
#include "command.h"
#include "error_status.h"

class User;

class Event {
	public:
		Event(int fd, int event_type);
		virtual ~Event();
		int		get_fd(void) const;
		int		get_event_type(void) const;
		const Command&	get_command(void) const;
		const std::vector<std::string>&	get_command_params(void) const;
		const ErrorStatus& get_error_status(void) const;
		void	set_command(const Command& command);
		void	set_command_params(const std::vector<std::string>& commmand_params);
		void	set_error_status(const ErrorStatus&);
		bool	HasErrorOccurred(void) const;
		virtual bool IsChannelEvent(void) const;
		void set_executer(const User&);
		const User& get_executer(void) const;
		void set_do_nothing(bool);
		bool is_do_nothing(void) const;
		void IncreaseUserCount(void);
		int get_user_count(void) const;
		std::string CreateErrorMessage(const User& user, const std::string& target = "") const;

		class NoErrorException : public std::runtime_error {
			public:
				NoErrorException(void);

			private:
				static const std::string kMessage;
		};
		class NoExecuterException : public std::runtime_error {
			public:
				NoExecuterException(void);

			private:
				static const std::string kMessage;
		};
		class AlreadySetException : public std::runtime_error {
			public:
				AlreadySetException(void);
			private:
				static const std::string kMessage;
		};

	protected:
		Event(const Event&);
		virtual std::string CreateTargetStr(const std::string&) const;

	private:
		const int	fd_;
		const int	event_type_;
		const Command* command_;
		std::vector<std::string>	command_params_;
		const ErrorStatus* error_status_;
		const User* executer_;
		bool is_do_nothing_;
		int user_count_;
};

#endif
