#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database) : _database(database)
{
	// PASS
}

void LoginManager::signup(const std::string& username, const std::string& password, const std::string& mail)
{
	//TODO
}

void LoginManager::login(const std::string& username, const std::string& password)
{
	//TODO
}

void LoginManager::logout(const std::string& username)
{
	//TODO
}
