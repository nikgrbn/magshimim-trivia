#include "Communicator.h"

Communicator::Communicator() : _handler_factory(RequestHandlerFactory(new SqliteDatabase)) {
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
		LoginRequestHandler* login_req_handler = this->_handler_factory.createLoginRequestHandler();
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
	RequestInfo request{};
	RequestResult response{};

	try {
		while (true) {
			request = receiveRequest(client_socket);
			
			if (this->RequestValidation(request, client_socket)) {
				response = (this->_clients.find(client_socket))->second->handleRequest(request); // handle request
			} else {
				sendError(client_socket, "[!] Invalid request", response);
			}

			sendResponse(client_socket, response);
		}
	} catch (const std::exception& e) {
		closesocket(client_socket);
		this->_clients.erase(client_socket);
	}
}

RequestInfo Communicator::receiveRequest(SOCKET client_socket) {
	unsigned int message_length{};
	RequestInfo request{};

	request.buffer = Buffer();
	request.buffer.resize(HEADER_SIZE);

	int status = recv(client_socket, (char*)request.buffer.data(), HEADER_SIZE, NULL); // recieve header content
	if (status <= 0) // checks if socket is up
		throw std::exception("Socket was closed");

	request.id = (ProtocolCodes)request.buffer[0]; // set the message code
	// Desirialize data length
	message_length = (request.buffer[CODE_SIZE]) | (request.buffer[CODE_SIZE + 1] << 8) | (request.buffer[CODE_SIZE + 2] << 16) | request.buffer[CODE_SIZE + 3] << 24;

	request.buffer.resize(HEADER_SIZE + message_length);
	if (message_length != 0)
		recv(client_socket, (char*)(request.buffer.data() + HEADER_SIZE), message_length, NULL); // receive message

	return request;
}

void Communicator::sendResponse(SOCKET client_socket, const RequestResult& response) {
	int sendExitCode = 0;

	sendExitCode = send(client_socket, (char*)response.buffer.data(), response.buffer.size(), NULL); //send response
	this->_clients.find(client_socket)->second = response.newHandler; //set new handler

	if (sendExitCode == SOCKET_ERROR) // checks if socket is up
		throw std::exception("connection was closed");
}

void Communicator::sendError(SOCKET clientSocket, const std::string& errorMessage, RequestResult& response) {
	ErrorResponse error_struct = {
		errorMessage
	};

	response.buffer = JsonResponsePacketSerializer::serializeResponse(error_struct);
	send(clientSocket, (char*)response.buffer.data(), response.buffer.size(), NULL);
}

bool Communicator::LoginRequestSanitizer(RequestInfo request) {
	if (request.buffer[0] == (unsigned int)ProtocolCodes::Login)
		return true;

	return false;
}

bool Communicator::RequestValidation(RequestInfo request, SOCKET client_socket) {
	if (this->_clients.find(client_socket)->second->IsRequestRelevant(request))
		return true;

	return false;
}
