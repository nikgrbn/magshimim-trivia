#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username) : _username(username)
{
	//PASS
}

std::string LoggedUser::getUsername()
{
	return this->_username;
}
