#pragma once

// Standard libraries
#include <iostream>
#include <map>

// Sockets libraries
#include <WinSock2.h>
#include <Windows.h>
//#include "WSAInitializer.h"

// Project header files
#include "IRequestHandler.h"

class Communicator
{
public:
	// CON's / DES's
	Communicator();
	~Communicator();

	// Public Methods
	void startHandleRequests();

private:
	// Private Methods
	void bindAndListen();
	void handleNewClient(SOCKET client_socket);

	// Members
	SOCKET _serverSocket;
	std::map <SOCKET, IRequestHandler*> _clients;
};