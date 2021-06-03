#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser& user) 
	: _request_handler_factory(factory), _user(user) {
}

bool MenuRequestHandler::IsRequestRelevant(RequestInfo info) {
	if (info.id >= ProtocolCodes::CreateRoomRequest && info.id <= ProtocolCodes::Login)
		return true;

	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info) {
	GetStatisticsResponse r;
	SqliteDatabase *db = new SqliteDatabase;
	StatisticsManager s(db);

	r.user_statistics = s.getStatistics();
	r.high_score = s.getHighScore();
	r.status = 100;

	JsonResponsePacketSerializer::serializeResponse(r);
	return RequestResult();
}

RequestResult MenuRequestHandler::signout(RequestInfo) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo) {
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo) {
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo) {
	return RequestResult();
}
