#pragma comment(lib, "ws2_32.lib")

#include "Server.h"

Server::Server() : _communicator() {
}

Server::~Server() {
}

void Server::run() {
	std::string user_input{};

	std::thread (&Communicator::startHandleRequests, &this->_communicator).detach(); // this->_communicator = this (pointer to class)

	// Admin pannel
	std::cout << "[!] Trivia server is up on port @" << SERVER_PORT << '\n';
	std::cout << "Hello Admin, do your own ->" << '\n';

	while (true) {
		std::cout << ">> ";
		std::cin >> user_input;

		// Quit the server
		if (user_input == "EXIT")
			break;
	}
}