#include <iostream>
#include <thread>

void adminPannel();

int main() {
	std::thread admin_pannel(adminPannel);
	admin_pannel.detach();

	while(true) {}

	return 0;
}

void adminPannel() {
	std::string user_input{};

	std::cout << "Hello Admin, Please enter commands ->" << '\n';
	while (true) {
		std::cout << ">> ";
		std::cin >> user_input;

		// Quit the server
		if (user_input == "EXIT")
			break;
	}
}