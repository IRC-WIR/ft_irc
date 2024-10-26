#ifndef DATABASE_H_
# define DATABASE_H_

# include "utils.h"
# include "finishable.h"
# include "event_listener.h"
# include "event_configurator.h"
# include "user.h"

class Database {

	public:
		Database(const std::string& password);
		~Database();

		void CreateUser(int fd);
		void CreateChannel(void);
		void DeleteFinishedElements(void);

		void CheckEvent(Event& event) const;
		std::map<int, std::string> ExecuteEvent(const Event& event);
		const std::string& get_server_password() const;
	private:
		Database();
		std::vector<EventConfigurator*> check_element_;
		std::vector<EventListener*> execute_element_;
		const std::string& server_password_;

		void CheckCommandAndParams(Event& event) const;
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

		// DeleteFinishedElements内で使う、vectorから用済みのものを取り除いてsetに追加する用の関数
		template <typename T, typename U>
		static void EraseAndAdd(T& t, U& u) {
			for (typename T::iterator it = t.begin(); it != t.end();) {
				if ((*it)->IsFinished()) {
					u.insert(*it);
					it = t.erase(it);
				} else
					++it;
			}
		}
};

#endif