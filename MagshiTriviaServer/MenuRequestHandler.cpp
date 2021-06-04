#include "LoginRequestHandler.h"
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
	RequestResult response;

	switch (info.id) {
	case ProtocolCodes::LogoutRequest: {
		response = this->signout(info);
		break;
	}

	case ProtocolCodes::GetRoomsRequest: {
		response = this->getRooms(info);
		break;
	}

	case ProtocolCodes::GetPlayersInRoomRequest: {
		response = this->getPlayersInRoom(info);
		break;
	}

	case ProtocolCodes::GetPersonalStats: {
		response = this->getPersonalStats(info);
		break;
	}

	case ProtocolCodes::HighScoreRequest: {
		response = this->getHighScore(info);
		break;
	}

	case ProtocolCodes::JoinRoomRequest: {
		response = this->joinRoom(info);
		break;
	}

	case ProtocolCodes::CreateRoomRequest: {
		response = this->createRoom(info);
		break;
	}
	}

	return response;
}

RequestResult MenuRequestHandler::signout(RequestInfo request) {
	RequestResult response{};
	LogoutResponse logout_response{};

	try {
		this->_request_handler_factory->getLoginManager().logout(this->_user.getUsername());
		logout_response.status = ResponseStatus::LogoutSuccess;
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	} catch (std::exception& e) {
		logout_response.status = ResponseStatus::LogoutError;
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(logout_response);
	return response;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request) {
	RequestResult response{};
	GetRoomsResponse get_rooms_response{};

	try {
		get_rooms_response.rooms = this->_request_handler_factory->getRoomManager().getRooms();
		response.newHandler = this->_request_handler_factory->createMenuRequestHandler(this->_user);
		get_rooms_response.status = ResponseStatus::GetRoomsSuccess;
	} catch (std::exception& e) {
		get_rooms_response.status = ResponseStatus::GetRoomsError;
		response.newHandler = this->_request_handler_factory->createMenuRequestHandler(this->_user);
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_rooms_response);
	return response;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request) {
	RequestResult response{};
	GetPlayersInRoomResponse get_players_in_room_response{};

	try {
		GetPlayersInRoomRequest room_request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
		std::vector<RoomData> rooms = this->_room_manager.getRooms();
		
		RoomData room_data;
		for (auto current_room : rooms) {
			if (current_room.id == room_request.roomId) {
				room_data = current_room;
				break;
			}
		}

		Room desired_room(room_data);
		get_players_in_room_response.players = desired_room.getAllUsers();
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();

	} catch (std::exception& e) {
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_players_in_room_response);
	return response;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request) {
	RequestResult response{};
	getPersonalStatsResponse get_personal_stats{};

	try {
		UserStatistics user_stats = this->_statistics_manager.getUserStatistics(this->_user.getUsername());
		std::string stats = user_stats.score + user_stats.total_answers + user_stats.games_played + user_stats.correct_answers + user_stats.average_answer_time;

		get_personal_stats.statistics = stats;
		get_personal_stats.status = ResponseStatus::GetPersonalStatsSuccess;
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	} catch (std::exception& e) {
		get_personal_stats.status = ResponseStatus::GetPersonalStatsError;
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_personal_stats);
	return response;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request) {
	/*RequestResult response{};
	getHighScoreResponse get_high_score{};

	try {
		std::vector<UserStatistics> high_score = this->_statistics_manager.getHighScore();
		get_high_score.status = ResponseStatus::HighScoreRequestSuccess;
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	} catch (std::exception& e) {
		get_high_score.status = ResponseStatus::HighScoreRequestError;
		response.newHandler = this->_request_handler_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_high_score);
	return response;*/
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo request) {
	RequestResult response{};
	JoinRoomResponse join_room_response{};

	try {
		JoinRoomRequest join_room_request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
		RoomData room_data(this->_room_manager.getRooms()[join_room_request.roomId]);
		Room room(room_data);

		room.addUser(this->_user);
		join_room_response.status = ResponseStatus::JoinRoomSuccess;
	} catch (std::exception& e) {
		join_room_response.status = ResponseStatus::JoinRoomError;
		response.newHandler = this->_request_handler_factory->createMenuRequestHandler(this->_user);
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(join_room_response);
	return response;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo request) {
	RequestResult response{};
	CreateRoomResponse create_room_response{};

	try {
		CreateRoomRequest create_room_request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);
		RoomData room_data;
		room_data.name = create_room_request.roomName;
		room_data.maxPlayers = create_room_request.maxUsers;
		room_data.numOfQuestionsInGame = create_room_request.questionCount;
		room_data.timePerQuestion = create_room_request.answerTimeout;

		this->_room_manager.createRoom(this->_user, room_data);
		create_room_response.status = ResponseStatus::CreateRoomSuccess;
	} catch (std::exception& e) {
		create_room_response.status = ResponseStatus::CreateRoomError;
		response.newHandler = this->_request_handler_factory->createMenuRequestHandler(this->_user);
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(create_room_response);
	return response;
}
