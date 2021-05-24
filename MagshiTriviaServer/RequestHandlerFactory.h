#pragma once

// Project header files
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory
{
public:
	// C'TORs / D'TORs
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager _login_manager;
	IDatabase* _data_base;

};