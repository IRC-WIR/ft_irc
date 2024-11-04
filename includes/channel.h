#ifndef CHANNEL_H_
# define CHANNEL_H_

#include "event_listener.h"
#include "event_configurator.h"
#include "utils.h"
#include "user.h"
#include "optional_message.h"
#include "response_status.h"
#include <stdexcept>
#include <map>
#include <sstream>

class Channel: public EventListener, public EventConfigurator {
	public:
		static const int kMaxJoiningChannels = 10;

		Channel(const User& op, const std::string& name);
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
		bool GiveOperator(const User&);
		bool TakeOperator(const User&);
		bool IsOperator(const User&) const;
		bool IsMode(const char& c) const;
		void set_topic(const std::string&);
		const std::string& get_topic(void) const;
		const std::string& get_name(void) const;
		const utils::MyVector<const User*>& get_members(void) const;
		std::string GenerateMemberList(void) const;
		std::string GenerateMemberListWithNewUser(const User&) const;

	private:
		template <typename T, typename U>
		class MyMap : public std::map<T, U> {
			public:
				const U& operator() (const T& key) const {
					const typename MyMap<T, U>::const_iterator it = this->find(key);
					if (it == this->end())
						throw std::out_of_range(MyMap<T, U>::kErrMsg);
					return it->second;
				}
			private:
				static const std::string kErrMsg;
		};

		const std::string name_;
		std::string topic_;
		// i,t,k,o,lは少なくとも実装
		MyMap<char, bool> mode_map_;
		std::string key_;
		std::size_t max_member_num_;
		utils::MyVector<const User*> operators_;
		utils::MyVector<const User*> members_;

		Channel(const Channel&);
		void InitModeMap(void);

		//check command
		void CkPassCommand(Event& event) const;
		void CkNickCommand(Event& event) const;
		void CkUserCommand(Event& event) const;
		void CkJoinCommand(Event*& event) const;
		void CkInviteCommand(Event& event) const;
		void CkKickCommand(Event& event) const;
		void CkTopicCommand(Event*& event) const;
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
