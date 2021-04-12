#include "Communicator.h"

Communicator::Communicator() {
}

Communicator::~Communicator() {
}

void Communicator::startHandleRequests() {
	this->bindAndListen();
	while (true) {
		SOCKET client_socket = ::accept(this->_serverSocket, NULL, NULL); //accept client
		if (client_socket == INVALID_SOCKET)
			throw std::exception("Error in function " __FUNCTION__ " : failed to establish the client connection");

		// insert new client to the map
		std::unique_lock<std::mutex> lck(this->_clients_lock);
		LoginRequestHandler login_req_handler; // new LoginRequestHandler instance
		this->_clients.emplace(client_socket, login_req_handler);
		lck.unlock();

		// creates new thread for the new client
		std::thread(&Communicator::handleNewClient, this, client_socket).detach();
	}
}

void Communicator::bindAndListen() {
	struct sockaddr_in sa = { 0 };

	// Socket address setup
	sa.sin_port = htons(SERVER_PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	// Socket binding
	if (bind(this->_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");

	return;
}

void Communicator::handleNewClient(SOCKET client_socket) {
	// TODO
}
