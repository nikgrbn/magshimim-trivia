#include "Communicator.h"

Communicator::Communicator() {
	WSADATA wsa_data = { };
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		throw std::exception("WSAStartup Failed");

	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator() {
	try {
		closesocket(this->_serverSocket);
	} catch (...) {}
}

void Communicator::startHandleRequests() {
	this->bindAndListen();

	while (true) {
		SOCKET client_socket = ::accept(this->_serverSocket, NULL, NULL); //accept client
		if (client_socket == INVALID_SOCKET)
			throw std::exception("Error in function " __FUNCTION__ " : failed to establish the client connection");

		// insert new client to the map
		std::unique_lock<std::mutex> lck(this->_clients_lock);
		LoginRequestHandler* login_req_handler; // new LoginRequestHandler instance
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
	try {
		std::string welcome_message = "Hello";
		send(client_socket, welcome_message.c_str(), welcome_message.size(), 0);

		char user_message[6];
		recv(client_socket, user_message, 5, 0);
		user_message[5] = 0;

		std::cout << "Client message: " << user_message << '\n';
		closesocket(client_socket);
	} catch (const std::exception& e) {
		closesocket(client_socket);
	}
}
