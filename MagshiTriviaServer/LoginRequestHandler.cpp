#include "LoginRequestHandler.h"

bool LoginRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::Signup || info.id == ProtocolCodes::Login);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info) {
	RequestResult response;

	// -- Tests --
	if (info.id == ProtocolCodes::Login) {
		LoginRequest l = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		LoginResponse r;
		r.status = 100;
		response.buffer = JsonResponsePacketSerializer::serializeResponse(r);
		response.newHandler = nullptr;
	} else if (info.id == ProtocolCodes::Signup) {
		SignupRequest l = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
		SignupResponse r_s;
		r_s.status = 100;
		response.buffer = JsonResponsePacketSerializer::serializeResponse(r_s);
		response.newHandler = nullptr;
	}
	// -- Tests --

	return response;
}