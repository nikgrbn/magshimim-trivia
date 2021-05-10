#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username) : _username(username)
{
	//PASS
}

std::string LoggedUser::getUsername() const
{
	return this->_username;
}

bool operator==(const LoggedUser& u1, const LoggedUser& u2)
{
	return u1.getUsername() == u2.getUsername();
}
