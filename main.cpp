#include <iostream>
#include <pqxx/pqxx>

#include "value.hpp"

int main(int argc, char ** argv) {
	if (argc <= 1) {
		std::cerr << "usage: " << argv[0] << " <db_uri>\n";
		return -1;
	}
	auto db_uri = argv[1];
	pqxx::connection C(db_uri);
	if (!C.is_open()) {
		std::cout << "failure :( \n";
		return -2;
	}
	std::cout << "success!\n";

	pqxx::work W(C);
	auto result = W.exec("SELECT * FROM playing_with_neon LIMIT 5;");

	for (const auto& row: result) {
		for (const auto& col: row) {
			std::cout << col << "; ";
		}
		std::cout << "\n";
	}
	W.commit();
	C.disconnect();

	std::cout << "woot!" << "\n";
	std::cout << 3.14159 / 2 << "\n";
	auto i64 = mnem::Value::Int(0xdeadbeef);
	return 0;
}
