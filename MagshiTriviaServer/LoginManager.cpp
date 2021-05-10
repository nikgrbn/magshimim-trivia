#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database) : _database(database)
{
	// PASS
}

void LoginManager::signup(const std::string& username, const std::string& password, const std::string& mail)
{
	// Check if such a user already exits
	if (!this->_database->doesUserExists(username))
	{
		// Add new user to database and vector
		this->_database->addNewUser(username, password, mail);
		this->_loggedUsers.push_back(LoggedUser(username));
	}
	// If username is taken - throw exception
	else
	{
		throw std::exception("User with such username already exists!");
	}
}

void LoginManager::login(const std::string& username, const std::string& password)
{
	// Check if passwords match
	if (this->_database->doesPasswordMatch(username, password))
	{
		// Push user to a vector
		this->_loggedUsers.push_back(LoggedUser(username));
	}
	// Throw exception if not
	else
	{
		throw std::exception("Invalid password or username!");
	}
}

void LoginManager::logout(const std::string& username)
{
	// Iterate through vector
	for (auto user : this->_loggedUsers)
	{
		// Remove users with matching username
		if (user.getUsername() == username)
		{
			this->_loggedUsers.erase(std::remove(this->_loggedUsers.begin(), this->_loggedUsers.end(), user),
				this->_loggedUsers.end());
			break;
		}
	}
}
