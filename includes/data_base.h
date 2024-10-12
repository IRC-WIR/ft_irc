#ifndef DATA_BASE_H_
	#define DATA_BASE_H_

#include "utils.h"
#include "event_listener.h"
#include "event_configurator.h"
#include "user.h"

class DataBase{

	public:
		DataBase();
		~DataBase();

		void createUser(int fd);
		void createChannel();
		std::vector<EventConfigurator*> get_check_element() const;
		std::vector<EventListener*> get_execute_element() const;

	private:
		std::vector<EventConfigurator*> check_element_;
		std::vector<EventListener*> execute_element_;

};

#endif