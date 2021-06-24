#pragma once

// Project header files
#include "ProtocolStructures.h"

class IRequestHandler
{
public:
	IRequestHandler() {};
	~IRequestHandler() {};

	virtual bool IsRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
	virtual void DisconnectUser() = 0;
	virtual RequestResult GetHandlerType() = 0;
};