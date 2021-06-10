#include "RequestHandlerFactory.h"

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

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user) {
	MenuRequestHandler* menu_req_handler = new MenuRequestHandler(this, user);

	return menu_req_handler;
}

RoomAdminRequestHanlder* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room room, RoomManager* room_manager) {
	RoomAdminRequestHanlder* room_admin_req_handler = new RoomAdminRequestHanlder(this, user, room, room_manager);

	return room_admin_req_handler;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user) {
	return nullptr;
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
