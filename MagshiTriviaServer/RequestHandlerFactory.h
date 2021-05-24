#pragma once

// Project header files
#include "LoginRequestHandler.h"
#include "LoginManager.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager _login_manager;
	IDatabase* _data_base;

};