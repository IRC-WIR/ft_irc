#ifndef DATABASE_H_
# define DATABASE_H_

# include "utils.h"
# include "finishable.h"
# include "event_listener.h"
# include "event_configurator.h"
# include "user.h"

class Database {

	public:
		Database();
		~Database();

		void CreateUser(int fd);
		void CreateChannel();
		void DeleteFinishedElements();

		void CheckEvent(Event& event) const;
		std::map<int, std::string> ExecuteEvent(const Event& event);

	private:
		std::vector<EventConfigurator*> check_element_;
		std::vector<EventListener*> execute_element_;

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