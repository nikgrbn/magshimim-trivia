#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory() : _login_manager(nullptr) {

}

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) 
	: _data_base(db), _login_manager(LoginManager(db)) {
}

RequestHandlerFactory::~RequestHandlerFactory() 
{ }

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	LoginRequestHandler* login_req_handler = new LoginRequestHandler(this->_login_manager, this);

	return login_req_handler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler() {
	MenuRequestHandler* menu_req_handler = new MenuRequestHandler();

	return menu_req_handler;
}

LoginManager& RequestHandlerFactory::getLoginManager()  {
	return this->_login_manager;
}

RoomManager& RequestHandlerFactory::getRoomManager() {
	return this->_room_manager;
}

StatisticsManager RequestHandlerFactory::getStatisticsManager() {
	return this->_statistics_manager;
}
