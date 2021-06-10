#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser& user, Room& room, RoomManager* room_manager)
	: _user(user), _handle_factory(factory), _room(room) , _room_manager(room_manager) {

}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{ }

bool RoomAdminRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::LogoutRequest || info.id == ProtocolCodes::CloseRoomRequest || info.id == ProtocolCodes::StartGameRequest || info.id == ProtocolCodes::GetRoomStateRequest || info.id == ProtocolCodes::GetHandlerTypeRequest || info.id == ProtocolCodes::GetRoomsRequest || info.id == ProtocolCodes::GetPlayersInRoomRequest);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info) {
	RequestResult response;

	switch (info.id)
	{
	case ProtocolCodes::LogoutRequest: {
		response = this->signout(info);
		break;
	}

	case ProtocolCodes::CloseRoomRequest: {
		response = this->closeRoom(info);
		break;
	}

	case ProtocolCodes::StartGameRequest: {
		response = this->startGame(info);
		break;
	}
	
	case ProtocolCodes::GetRoomStateRequest: {
		response = this->getRoomState(info);
		break;
	}
	case ProtocolCodes::GetHandlerTypeRequest: {
		response = this->GetHandlerType();
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
	default:
		break;
	}

	return response;
}

void RoomAdminRequestHandler::DisconnectUser()
{ 
	this->_handle_factory->getLoginManager().logout(this->_user.getUsername());
}

RequestResult RoomAdminRequestHandler::GetHandlerType() {
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

RequestResult RoomAdminRequestHandler::signout(RequestInfo request)
{
	RequestResult response{};
	LogoutResponse logout_response{};

	try {
		this->_handle_factory->getLoginManager().logout(this->_user.getUsername());
		logout_response.status = ResponseStatus::LogoutSuccess;
		response.newHandler = this->_handle_factory->createLoginRequestHandler();
	}
	catch (std::exception& e) {
		logout_response.status = ResponseStatus::LogoutError;
		response.newHandler = this->_handle_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(logout_response);
	return response;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info) {
	RequestResult response{};
	CloseRoomResponse close_room_response{};

	try {
		this->_room_manager->deleteRoom(this->_room.getRoomData().id);
		response.newHandler = this->_handle_factory->createMenuRequestHandler(this->_user);
		close_room_response.status = ResponseStatus::CloseRoomRequestSuccess;
	} catch (std::exception& e) {
		response.newHandler = this;
		close_room_response.status = ResponseStatus::CloseRoomRequestSuccess;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(close_room_response);
	return response;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info) {
	RequestResult response{};
	StartGameResponse start_game_response{};

	try {
		this->_room.activateRoom(); // TODO: fix
		response.newHandler = this;
		start_game_response.status = ResponseStatus::StartGameRequestSuccess;
	} catch (std::exception& e) {
		response.newHandler = this;
		start_game_response.status = ResponseStatus::StartGameRequestError;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(start_game_response);
	return response;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info) {
	RequestResult response{};
	GetRoomStateResponse get_room_state_response{};

	try {
		RoomData room_data = this->_room.getRoomData();
		get_room_state_response.players = this->_room.getAllUsers();
		get_room_state_response.questionCount = room_data.numOfQuestionsInGame;
		get_room_state_response.hasGameBegun = room_data.isActive;
		get_room_state_response.answerTimeout = room_data.timePerQuestion;

		response.newHandler = this;
		get_room_state_response.status = ResponseStatus::GetRoomStateRequestSuccess;
	} catch (std::exception& e) {
		response.newHandler = this;
		get_room_state_response.status = ResponseStatus::GetRoomStateRequestError;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_room_state_response);
	return response;
}

RequestResult RoomAdminRequestHandler::getRooms(RequestInfo request)
{
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

RequestResult RoomAdminRequestHandler::getPlayersInRoom(RequestInfo request)
{
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
		response.newHandler = this;
	}
	catch (std::exception& e) {
		response.newHandler = this;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_players_in_room_response);
	return response;
}
