#ifndef CHANNEL_H_
# define CHANNEL_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"
#include "user.h"
#include "optional_message.h"
#include <stdexcept>

class Channel: public EventListener, public EventConfigurator {
	public:
		// max_numは仮
		Channel(const User& op, const std::string& name,
				const std::string& key = "", int max_num = 10);
		~Channel();

		void CheckCommand(Event*& event) const;
		OptionalMessage ExecuteCommand(const Event& event);
		bool IsFinished(void) const;
		void AddUser(const User&);
		bool RemoveUser(const User&);
		// 最初にnicknameが一致したUserを削除
		bool RemoveUserByNick(const std::string&);
		bool ContainsUser(const User&) const;
		bool ContainsUserByNick(const std::string&) const;
		void set_operator(const User&);
		const User& get_operator(void) const;
		void set_topic(const std::string&);
		const std::string& get_topic(void) const;
		const std::string& get_name(void) const;
		bool VerifyKey(const std::string&) const;

		class NoOperatorException : public std::runtime_error {
			public:
				NoOperatorException(void);

			private:
				static const std::string kErrorMessage;
		};

	private:
		const std::string name_;
		const std::string key_;
		const int max_member_num_;
		std::string topic_;
		//bool i_mode;
		//bool t_mode;
		//bool k_mode;
		//bool o_mode;
		//bool l_mode;
		std::vector<const User*> users_;
		const User* operator_;

		void RemoveUserBasic(std::vector<const User*>::iterator&);

		//check command
		void CkPassCommand(Event& event) const;
		void CkNickCommand(Event& event) const;
		void CkUserCommand(Event& event) const;
		void CkJoinCommand(Event& event) const;
		void CkInviteCommand(Event& event) const;
		void CkKickCommand(Event& event) const;
		void CkTopicCommand(Event& event) const;
		void CkModeCommand(Event& event) const;
		void CkPrivmsgCommand(Event& event) const;
		void CkQuitCommand(Event& event) const;

		//execute command
		OptionalMessage ExPassCommand(const Event& event);
		OptionalMessage ExNickCommand(const Event& event);
		OptionalMessage ExUserCommand(const Event& event);
		OptionalMessage ExJoinCommand(const Event& event);
		OptionalMessage ExInviteCommand(const Event& event);
		OptionalMessage ExKickCommand(const Event& event);
		OptionalMessage ExTopicCommand(const Event& event);
		OptionalMessage ExModeCommand(const Event& event);
		OptionalMessage ExPrivmsgCommand(const Event& event);
		OptionalMessage ExQuitCommand(const Event& event);
};

#endif
