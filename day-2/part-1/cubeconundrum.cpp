#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

bool	checkColorRules(std::string& token) {
	std::istringstream	iss(token);
	std::string			item;
	size_t				quantity;
	size_t redCount = 0, greenCount = 0, blueCount = 0;

	while (std::getline(iss, item, ',')) {
		quantity = std::stoi(item.substr(item.find_first_of("0123456789")));
		if (item.find("red") != std::string::npos)
			redCount += quantity;
		else if (item.find("green") != std::string::npos)
			greenCount += quantity;
		else if (item.find("blue") != std::string::npos)
			blueCount += quantity;
		else
			return (0);
	}
	return (redCount <= 12) && (greenCount <= 13) && (blueCount <= 14);
}

int		checkIsValid(std::string line, int index) {
	std::istringstream 			iss(line);
	std::string					token;

	while (std::getline(iss, token, ';')) {
		if (!checkColorRules(token))
			return (0);
	}
	return (index);
}

int		main(void) {
    std::ifstream	file("puzzle");
	size_t			index;
	size_t			sum;
    std::string 	line;
	size_t			colon_pos;

	if (!file.is_open()) {
		std::cout << "Unable to open file" << std::endl;
		return (1);
	}
	index = 1;
	sum = 0;
	while (std::getline(file, line)) {
		colon_pos = line.find(':');
		line = line.substr(colon_pos + 2);
		sum += checkIsValid(line, index);
		index++;
	}
	std::cout << sum << std::endl;
	file.close();

    return 0;
}
