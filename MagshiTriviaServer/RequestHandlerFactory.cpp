#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) 
	: _data_base(db), _login_manager(LoginManager(db)) {
}

RequestHandlerFactory::~RequestHandlerFactory() 
{ }

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	LoginRequestHandler* login_req_handler = new LoginRequestHandler(this->_login_manager, this);

	return login_req_handler;
}

LoginManager& RequestHandlerFactory::getLoginManager() {
	return this->_login_manager;
}
