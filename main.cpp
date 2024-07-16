#include <iostream>
#include <pqxx/pqxx>

int main(int argc, char ** argv) {
	if (argc <= 1) {
		std::cerr << "usage: " << argv[0] << " <db_uri>\n";
		return -1;
	}
	auto db_uri = argv[1];
	pqxx::connection C(db_uri);
	if (C.is_open()) {
		std::cout << "success!\n";
	} else {
		std::cout << "failure :( \n";
	}
	std::cout << "woot!" << "\n";
	std::cout << 3.14159 / 2 << "\n";
	return 0;
}
