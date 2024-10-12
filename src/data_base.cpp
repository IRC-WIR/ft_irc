#include "data_base.h"


DataBase::DataBase(){};
DataBase::~DataBase(){};

void DataBase::createUser(int fd)
{
	try
	{
		User* user = new User(fd);
		check_element_.push_back(user);
		execute_element_.push_back(user);
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << "bad to alloc memory" << e.what() << '\n';
	}
}

std::vector<EventConfigurator*> DataBase::get_check_element() const
{
	return check_element_;
}

std::vector<EventListener*> DataBase::get_execute_element() const
{
	return execute_element_;
}