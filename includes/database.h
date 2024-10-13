#ifndef DATABASE_H_
	#define DATABASE_H_

#include "utils.h"
#include "event_listener.h"
#include "event_configurator.h"
#include "user.h"

class Database{

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
};

#endif