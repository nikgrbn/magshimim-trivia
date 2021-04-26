#include "LoginRequestHandler.h"

bool LoginRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::Signup || info.id == ProtocolCodes::Login);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info) {
	RequestResult response;

	// -- Tests --

	LoginRequest l = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	LoginResponse r;
	r.status = 100;

	// ...

	response.buffer = JsonResponsePacketSerializer::serializeResponse(r);
	response.newHandler = nullptr;

	// -- Tests --
}