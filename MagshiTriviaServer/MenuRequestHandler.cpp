#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser& user, RoomManager* room_manager) 
	: _request_handler_factory(factory), _user(user), _room_manager(room_manager) {

	SqliteDatabase* db = new SqliteDatabase();
	this->_statistics_manager = StatisticsManager(db);
}

MenuRequestHandler::~MenuRequestHandler() {
	
}

bool MenuRequestHandler::IsRequestRelevant(RequestInfo info) {
	if (info.id >= ProtocolCodes::CreateRoomRequest && info.id <= ProtocolCodes::GetPersonalStats)
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

	case ProtocolCodes::GetHandlerTypeRequest: {
		response = this->GetHandlerType();
		break;
	}
	}

	return response;
}

void MenuRequestHandler::DisconnectUser() {
	this->_request_handler_factory->getLoginManager().logout(this->_user.getUsername());
}

RequestResult MenuRequestHandler::GetHandlerType() {
	RequestResult response;
	GetHandlerTypeResponse handler_type_response;

	try {
		handler_type_response.request_handler = this;
		handler_type_response.status = ResponseStatus::GetHandlerTypeRequestSuccess;
		response.newHandler = this;
	} catch (std::exception& e) {
		handler_type_response.status = ResponseStatus::GetHandlerTypeRequestError;
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(handler_type_response);
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
	std::vector<RoomData> roomsDatas;

	try {
		std::vector<Room> rooms = this->_room_manager->getRooms();
		for (auto room : rooms)
		{
			roomsDatas.push_back(room.getRoomData());
		}
		get_rooms_response.rooms = roomsDatas;
		response.newHandler = this;
		get_rooms_response.status = ResponseStatus::GetRoomsSuccess;
	}
	catch (std::exception& e) {
		get_rooms_response.status = ResponseStatus::GetRoomsError;
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_rooms_response);
	return response;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request) {
	RequestResult response{};
	GetPlayersInRoomResponse get_players_in_room_response{};

	try {
		GetPlayersInRoomRequest room_request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
		std::vector<Room> rooms = this->_room_manager->getRooms();

		for (auto current_room : rooms) {
			if (current_room.getRoomData().id == room_request.roomId) {
				get_players_in_room_response.players = current_room.getAllUsers();
				break;
			}
		}

		get_players_in_room_response.status = ResponseStatus::GetPlayersInRoomRequestSuccess;
		response.newHandler = this;
	}
	catch (std::exception& e) {
		get_players_in_room_response.status = ResponseStatus::GetPlayersInRoomRequestError;
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_players_in_room_response);
	return response;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request) {
	RequestResult response{};
	getPersonalStatsResponse get_personal_stats{};

	try {
		UserStatistics user_stats = this->_statistics_manager.getUserStatistics(this->_user.getUsername());
		std::string stats =  user_stats.average_answer_time + ", " + user_stats.games_played + ", " + user_stats.correct_answers + ", " + user_stats.total_answers + ", " + user_stats.score;
		get_personal_stats.statistics = stats;
		get_personal_stats.status = ResponseStatus::GetPersonalStatsSuccess;
		response.newHandler = this;
	} catch (std::exception& e) {
		get_personal_stats.status = ResponseStatus::GetPersonalStatsError;
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_personal_stats);
	return response;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request) {
	RequestResult response{};
	getHighScoreResponse get_high_score_response{};

	try {
		std::vector<UserStatistics> high_score = this->_statistics_manager.getHighScore();
		std::vector<std::string> high_score_strings{};

		for (auto user : high_score) {
			std::string current_user_stats = user.username + ", " + user.average_answer_time + ", " + user.games_played + ", " + user.correct_answers + ", " + user.total_answers + ", " + user.score;
			high_score_strings.push_back(current_user_stats);
		}
		
		get_high_score_response.statistics = high_score_strings;
		get_high_score_response.status = ResponseStatus::HighScoreRequestSuccess;
		response.newHandler = this;
	} catch (std::exception& e) {
		get_high_score_response.status = ResponseStatus::HighScoreRequestError;
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_high_score_response);
	return response;
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo request) {
	RequestResult response{};
	JoinRoomResponse join_room_response{};
	RoomData room_data{};

	try {
		JoinRoomRequest join_room_request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
		
		std::vector<Room> rooms_vector = this->_room_manager->getRooms();

		for (Room room : rooms_vector) {
			if (room.getRoomData().id == join_room_request.roomId)
			{
				this->_room_manager->InsertUserIntoRoom(join_room_request.roomId, this->_user);
				join_room_response.status = ResponseStatus::JoinRoomSuccess;
				response.newHandler = this->_request_handler_factory->createRoomMemberRequestHandler(this->_user, this->_room_manager->getRooms()[join_room_request.roomId - 1]);
				break;
			}
		}
	} catch (std::exception& e) {
		join_room_response.status = ResponseStatus::JoinRoomError;
		response.newHandler = this;
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
		room_data.isActive = inactive;

		room_data.id = this->_room_manager->createRoom(this->_user, room_data);

		response.newHandler = this->_request_handler_factory->createRoomAdminRequestHandler(this->_user, room_data);
		create_room_response.status = ResponseStatus::CreateRoomSuccess;
		create_room_response.roomId = room_data.id;
	} catch (std::exception& e) {
		create_room_response.status = ResponseStatus::CreateRoomError;
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(create_room_response);
	return response;
}
