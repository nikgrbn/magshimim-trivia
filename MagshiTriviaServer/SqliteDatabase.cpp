#include "SqliteDatabase.h"

// Callback functions
int isExists_callback(void* data, int argc, char** argv, char** azColName);

// Global flag
bool flag;

SqliteDatabase::SqliteDatabase()
{
	int doesFileExist = _access(dbFileName.c_str(), 0);

	// Open database
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK)
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
	}

	// If database doesn't exists
	const char* com;
	if (doesFileExist == -1)
	{

		// Create Users table
		com = "CREATE TABLE USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, MAIL TEXT NOT NULL);";
		res = sqlite3_exec(db, com, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "Failed to create DB [CODE: " << res << "]" << std::endl;
		}
	}
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(db);
	db = nullptr;
}

bool SqliteDatabase::doesUserExists(std::string username)
{
	flag = false;

	// Find user
	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT * FROM Users WHERE username = '%s';", username.c_str());
	sqlite3_exec(db, sql_com, isExists_callback, nullptr, errMessage);

	return flag;
}

bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
	flag = false;

	// Check password by username
	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT * FROM Users WHERE username = '%s' AND password = '%s';", username.c_str(), password.c_str());
	sqlite3_exec(db, sql_com, isExists_callback, nullptr, errMessage);

	return flag;
}

void SqliteDatabase::addNewUser(std::string username, std::string password, std::string mail)
{
	// Insert new user
	char sql_com[1024];
	snprintf(sql_com, 1024, "INSERT INTO Users (username, password, mail) VALUES ('%s', '%s', '%s');",
		username.c_str(), password.c_str(), mail.c_str());
	int res = sqlite3_exec(db, sql_com, nullptr, nullptr, errMessage);
}

int isExists_callback(void* data, int argc, char** argv, char** azColName)
{
	if (argc > 0)
	{
		flag = true;
	}
	return 0;
}