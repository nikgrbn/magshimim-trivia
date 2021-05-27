// Standard libraries
#include <iostream>

// Project libraries
#include "Server.h"

int main() {

	try {
		Server server_obj;
		server_obj.run();
	} catch (std::exception& e) {
		std::cout << "Error! - " << e.what() << '\n';
	}

	return 0;
}