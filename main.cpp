#include "data_validation.h"

int main() {
	std::cout << "Select the data you want to validate." << std::endl;
	std::cout << "1.URL\n2.email\n3.date\n4.number" << std::endl;
	int num{};
	std::cin >> num;
	std::cout << "Enter the data." << std::endl;
	std::string data;
	std::cin >> data;
	switch (num) {
	case 1:
		std::cout << is_valid_url(data) << std::endl;
		break;
	case 2:
		std::cout << is_valid_email(data) << std::endl;
		break;

	case 3:
		std::cout << is_valid_date(data) << std::endl;
		break;
	case 4:
		std::cout << is_valid_number(data) << std::endl;
		break;
	}
	return 0;
}