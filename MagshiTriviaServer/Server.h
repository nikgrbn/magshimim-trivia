#pragma once

// Project libraries
#include "Communicator.h"

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