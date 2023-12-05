#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void	checkColorRules(std::string& token, size_t *red, size_t *green, size_t *blue) {
	std::istringstream	iss(token);
	std::string			item;
	size_t				quantity;

	while (std::getline(iss, item, ',')) {
		quantity = std::stoi(item.substr(item.find_first_of("0123456789")));
		if (item.find("red") != std::string::npos) {
			if (quantity > *(red))
				*(red) = quantity;
		} else if (item.find("green") != std::string::npos) {
			if (quantity > *(green))
				*(green) = quantity;
		} else if (item.find("blue") != std::string::npos) {
			if (quantity > *(blue))
				*(blue) = quantity;
		}
	}
}

int		checkIsValid(std::string line) {
	std::istringstream 	iss(line);
	std::string			token;
	size_t redCount = 0, greenCount = 0, blueCount = 0;

	while (std::getline(iss, token, ';')) {
		checkColorRules(token, &redCount, &greenCount, &blueCount);
	}
	return (redCount * greenCount * blueCount);
}

int		main(void) {
    std::ifstream	file("puzzle");
	size_t			sum;
    std::string 	line;
	size_t			colon_pos;

	if (!file.is_open()) {
		std::cout << "Unable to open file" << std::endl;
		return (1);
	}
	sum = 0;
	while (std::getline(file, line)) {
		colon_pos = line.find(':');
		line = line.substr(colon_pos + 2);
		sum += checkIsValid(line);
	}
	std::cout << "sum is " << sum << std::endl;
	file.close();

    return 0;
}
