#pragma once

// Project header files
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

private:

};