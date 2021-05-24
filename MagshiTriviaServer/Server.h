#pragma once

// Standard libraries
#include <thread>

// Project libraries
#include "Communicator.h"
#include "StatusCodes.h"

class Server
{
public:
	// CON's / DES's
	Server();
	~Server();

	// Public Methods
	void run();

private:
	IDatabase* _data_base;
	RequestHandlerFactory _handle_factory;
	Communicator _communicator;
};