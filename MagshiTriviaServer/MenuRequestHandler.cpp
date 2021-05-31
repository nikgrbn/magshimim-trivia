#include "MenuRequestHandler.h"

bool MenuRequestHandler::IsRequestRelevant(RequestInfo info) {
	if (info.id >= ProtocolCodes::CreateRoomRequest && info.id <= ProtocolCodes::Login)
		return true;

	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info) {
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
