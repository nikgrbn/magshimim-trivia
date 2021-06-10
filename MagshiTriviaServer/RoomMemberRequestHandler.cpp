#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* factory, LoggedUser& user, Room& room, RoomManager* room_manager)
	: _user(user), _handle_factory(factory), _room(room), _room_manager(room_manager) {

}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{ }

bool RoomMemberRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::LeaveRoomRequest || info.id == ProtocolCodes::StartGameRequest || info.id == ProtocolCodes::GetRoomStateRequest || info.id == ProtocolCodes::GetRoomsRequest || info.id == ProtocolCodes::GetPlayersInRoomRequest);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info) {
	RequestResult response;

	switch (info.id)
	{
	case ProtocolCodes::LeaveRoomRequest: {
		response = this->leaveRoom(info);
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

void RoomMemberRequestHandler::DisconnectUser()
{ }

RequestResult RoomMemberRequestHandler::GetHandlerType() {
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info) {
	RequestResult response{};
	LeaveRoomResponse leave_room_response{};

	try {
		this->_room.removeUser(this->_user);
		leave_room_response.status = ResponseStatus::LeaveRoomRequestSucces;
		response.newHandler = this->_handle_factory->createMenuRequestHandler(this->_user);
	} catch (std::exception& e) {
		leave_room_response.status = ResponseStatus::LeaveRoomRequestError;
		response.newHandler = this->_handle_factory->createMenuRequestHandler(this->_user);
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(leave_room_response);
	return response;
}

RequestResult RoomMemberRequestHandler::startGame(RequestInfo info) {
	/*TODO: realize what the fuck this method does */
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info) {
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

RequestResult RoomMemberRequestHandler::getRooms(RequestInfo request)
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

RequestResult RoomMemberRequestHandler::getPlayersInRoom(RequestInfo request)
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
