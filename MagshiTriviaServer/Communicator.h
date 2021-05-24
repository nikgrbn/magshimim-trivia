#pragma once

// Standard libraries
#include <iostream>
#include <map>
#include <mutex>
#include <thread>

// Sockets libraries
#include <WinSock2.h>
#include <Windows.h>

// Project header files
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"
#include "StatusCodes.h"

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
	RequestInfo receiveRequest(SOCKET client_socket);
	void sendResponse(SOCKET client_socket, const RequestResult& response);
	void sendError(SOCKET clientSocket, const std::string& errorMessage, RequestResult& response);

	// Members
	SOCKET _serverSocket;
	RequestHandlerFactory _handler_factory;
	std::map <SOCKET, IRequestHandler*> _clients;
	std::mutex _clients_lock;
};