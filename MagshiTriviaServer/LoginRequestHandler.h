#pragma once

// Project header files
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = delete;
	LoginRequestHandler(LoginManager& login_manager, RequestHandlerFactory* handler_factory);
	~LoginRequestHandler();

	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	void DisconnectUser() override;
	RequestResult GetHandlerType() override;

private:
	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);

	LoginManager& _login_manager;
	RequestHandlerFactory* _handler_factory;
};