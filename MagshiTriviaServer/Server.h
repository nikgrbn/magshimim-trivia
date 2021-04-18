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
	Communicator _communicator;
};