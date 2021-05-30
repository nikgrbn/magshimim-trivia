#include "SqliteDatabase.h"

// Callback functions
int isExists_callback(void* data, int argc, char** argv, char** azColName);
int getUsers_callback(void* data, int argc, char** argv, char** azColName);
int getQuestions_callback(void* data, int argc, char** argv, char** azColName);
int getTotalAnswers_callback(void* data, int argc, char** argv, char** azColName);
int getCorrectAnswers_callback(void* data, int argc, char** argv, char** azColName);
int getTimePlayed_callback(void* data, int argc, char** argv, char** azColName);
int getTotalGames_callback(void* data, int argc, char** argv, char** azColName);

// Global variables
bool flag;
std::vector<std::string> global_users_vector;
std::list<Question> global_question_list;
int counter;
float time_played;

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

		// Create Statistics table
		com = "CREATE TABLE STATISTICS (USERNAME TEXT PRIMARY KEY NOT NULL, TIME_PLAYED FLOAT DEFAULT 0.0, TOTAL_ANSWERS INTEGER DEFAULT 0, CORRECT_ANSWERS INTEGER DEFAULT 0, TOTAL_GAMES INTEGER DEFAULT 0);";
		res = sqlite3_exec(db, com, nullptr, nullptr, errMessage);

		// Create Questionaree table
		com = "CREATE TABLE Questions (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, FIRST_A TEXT NOT NULL, SECOND_A TEXT NOT NULL, THIRD_A TEXT NOT NULL, FOURTH_A TEXT NOT NULL, CORRECT_A TEXT NOT NULL);";
		res = sqlite3_exec(db, com, nullptr, nullptr, errMessage);

		// Fill table with questions
		Questionnaire q;
		std::list<Question> question_list = q.getQuestionList();

		for (auto quest : question_list)
		{
			char sql_com[1024];
			snprintf(sql_com, 1024,
				"INSERT INTO QUESTIONS (QUESTION, FIRST_A, SECOND_A, THIRD_A, FOURTH_A, CORRECT_A) VALUES ('%s', '%s', '%s', '%s', '%s', %d);",
				quest.question.c_str(), quest.answers[0].c_str(), quest.answers[1].c_str(), quest.answers[2].c_str(), quest.answers[3].c_str(), quest.correct_ans);
			sqlite3_exec(db, sql_com, nullptr, nullptr, errMessage);
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
	// Insert new user to a user table
	char sql_com[1024];
	snprintf(sql_com, 1024, "INSERT INTO Users (username, password, mail) VALUES ('%s', '%s', '%s');",
		username.c_str(), password.c_str(), mail.c_str());
	int res = sqlite3_exec(db, sql_com, nullptr, nullptr, errMessage);

	// Insert new user to a statistics table
	snprintf(sql_com, 1024, "INSERT INTO STATISTICS (username) VALUES ('%s');", username.c_str());
	res = sqlite3_exec(db, sql_com, nullptr, nullptr, errMessage);
}

std::vector<std::string> SqliteDatabase::getUsers()
{
	global_users_vector.clear();

	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT USERNAME FROM USERS;");
	sqlite3_exec(db, sql_com, getUsers_callback, nullptr, errMessage);

	return global_users_vector;
}

std::list<Question> SqliteDatabase::getQuestions(int num)
{
	global_question_list.clear();

	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT %d;", num);
	sqlite3_exec(db, sql_com, getQuestions_callback, nullptr, errMessage);

	return global_question_list;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
	time_played = 0;

	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT TIME_PLAYED FROM STATISTICS WHERE USERNAME = '%s';", username.c_str());
	sqlite3_exec(db, sql_com, getTimePlayed_callback, nullptr, errMessage);

	int total_ans = SqliteDatabase::getNumOfTotalAnswers(username);
	return total_ans == 0 ? 0.0 : time_played / total_ans;
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
	counter = 0;

	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT CORRECT_ANSWERS FROM STATISTICS WHERE USERNAME = '%s';", username.c_str());
	sqlite3_exec(db, sql_com, getCorrectAnswers_callback, nullptr, errMessage);

	return counter;
}

int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
	counter = 0;

	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT TOTAL_ANSWERS FROM STATISTICS WHERE USERNAME = '%s';", username.c_str());
	sqlite3_exec(db, sql_com, getTotalAnswers_callback, nullptr, errMessage);

	return counter;
}

int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
	counter = 0;

	char sql_com[1024];
	snprintf(sql_com, 1024, "SELECT TOTAL_GAMES FROM STATISTICS WHERE USERNAME = '%s';", username.c_str());
	sqlite3_exec(db, sql_com, getTotalGames_callback, nullptr, errMessage);

	return counter;
}

int isExists_callback(void* data, int argc, char** argv, char** azColName)
{
	if (argc > 0)
	{
		flag = true;
	}
	return 0;
}

int getUsers_callback(void* data, int argc, char** argv, char** azColName)
{
	std::string username{};

	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "USERNAME") {
			username = argv[i];
		}
	}

	global_users_vector.push_back(username);

	return 0;
}

int getQuestions_callback(void* data, int argc, char** argv, char** azColName)
{
	std::string question;
	std::string answers[4];
	unsigned int correct_ans = 0;

	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "QUESTION") {
			question = argv[i];
		}
		else if (std::string(azColName[i]) == "FIRST_A") {
			answers[0] = argv[i];
		}
		else if (std::string(azColName[i]) == "SECOND_A") {
			answers[1] = argv[i];
		}
		else if (std::string(azColName[i]) == "THIRD_A") {
			answers[2] = argv[i];
		}
		else if (std::string(azColName[i]) == "FOURTH_A") {
			answers[3] = argv[i];
		}
		else if (std::string(azColName[i]) == "CORRECT_A") {
			correct_ans = atoi(argv[i]);
		}
	}

	global_question_list.push_back(Question(question, answers[0], answers[1], answers[2], answers[3], correct_ans));
	
	return 0;
}

int getTotalAnswers_callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "TOTAL_ANSWERS") {
			counter = atoi(argv[i]);
		}
	}

	return 0;
}

int getCorrectAnswers_callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "CORRECT_ANSWERS") {
			counter = atoi(argv[i]);
		}
	}

	return 0;
}


int getTimePlayed_callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "TIME_PLAYED") {
			time_played = std::stof(argv[i]);
		}
	}

	return 0;
}

int getTotalGames_callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "TOTAL_GAMES") {
			counter = atoi(argv[i]);
		}
	}

	return 0;
}