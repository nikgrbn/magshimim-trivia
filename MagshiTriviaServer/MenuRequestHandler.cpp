#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser& user) 
	: _request_handler_factory(factory), _user(user) {
}

bool MenuRequestHandler::IsRequestRelevant(RequestInfo info) {
	if (info.id >= ProtocolCodes::CreateRoomRequest && info.id <= ProtocolCodes::Login)
		return true;

	return false;
}

/*
	GetStatisticsResponse r;
	SqliteDatabase *db = new SqliteDatabase;
	StatisticsManager s(db);

	r.user_statistics = s.getStatistics();
	r.high_score = s.getHighScore();
	r.status = 100;

	JsonResponsePacketSerializer::serializeResponse(r);
*/
RequestResult MenuRequestHandler::handleRequest(RequestInfo info) {
	switch (info.id) {
	case ProtocolCodes::LogoutRequest: {
		break;
	}

	case ProtocolCodes::GetRoomsRequest: {
		break;
	}

	case ProtocolCodes::GetPlayersInRoomRequest: {
		break;
	}

	case ProtocolCodes::GetPersonalStats: {
		break;
	}

	case ProtocolCodes::HighScoreRequest: {
		break;
	}

	case ProtocolCodes::JoinRoomRequest: {
		break;
	}

	case ProtocolCodes::CreateRoomRequest: {
		break;
	}
	}
	return RequestResult();
}

RequestResult MenuRequestHandler::signout(RequestInfo request) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request) {
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request) {
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo request) {
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo request) {
	return RequestResult();
}
