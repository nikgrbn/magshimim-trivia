#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() : _login_manager(nullptr) {

}

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) 
	: _data_base(db), _login_manager(LoginManager(db)), _room_manager(new RoomManager()) {
}

RequestHandlerFactory::~RequestHandlerFactory() {
	delete this->_room_manager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	LoginRequestHandler* login_req_handler = new LoginRequestHandler(this->_login_manager, this);

	return login_req_handler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user) {
	MenuRequestHandler* menu_req_handler = new MenuRequestHandler(this, user, this->_room_manager);

	return menu_req_handler;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room room) {
	RoomAdminRequestHandler* room_admin_req_handler = new RoomAdminRequestHandler(this, user, room, this->_room_manager);

	return room_admin_req_handler;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room room) {
	RoomMemberRequestHandler* room_member_req_handler = new RoomMemberRequestHandler(this, user, room, this->_room_manager);

	return room_member_req_handler;
}

LoginManager& RequestHandlerFactory::getLoginManager()  {
	return this->_login_manager;
}

RoomManager* RequestHandlerFactory::getRoomManager() {
	return this->_room_manager;
}

StatisticsManager RequestHandlerFactory::getStatisticsManager() {
	return this->_statistics_manager;
}
