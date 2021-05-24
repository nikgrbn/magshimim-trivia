#pragma once

// Project header files
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

private:
	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);

	LoginManager& _login_manager;

};