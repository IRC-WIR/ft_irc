#include "database.h"


Database::Database(){};
Database::~Database(){};

void Database::CreateUser(int fd)
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

void Database::CheckEvent(Event& event) const
{
	std::size_t vector_length = check_element_.size();
	for (std::size_t i = 0; i < vector_length; i++)
	{
		check_element_[i] -> CheckCommand(event);
	}
}

std::map<int, std::string>*	Database::ExecuteEvent(const Event& event){
	std::map<int, std::string>*ret = new std::map<int, std::string>();
	//未完成、下記配慮が必要
	//①別ブランチでretにpairからmap<int, std::string>に入力する変換が必要）
	//②ExecuteCommandからはnewしたpairが帰ってくるので、map<int, std::string>もnewするなら、pairを先にdeleteをするべき！？
	std::size_t vector_length = execute_element_.size();
	for (size_t i = 0; i < vector_length; i++)
	{
		execute_element_[i] -> ExecuteCommand(event);
	}
	return ret;
}

void	Database::DeleteFinishedElements()
{
	std::set<Finishable *> ptr_set;

	Database::erase_and_add(check_element_, ptr_set);
	Database::erase_and_add(execute_element_, ptr_set);

	for (std::set<Finishable *>::iterator it = ptr_set.begin(); it != ptr_set.end(); ++it)
		delete *it;
}
