#include "LoginRequestHandler.h"

bool LoginRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::Signup || info.id == ProtocolCodes::Login);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info) {
	// TODO: implement
	RequestResult res;
}