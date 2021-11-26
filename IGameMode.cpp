#include "IGameMode.h"

bool IGameMode::validateInput(std::string input)
{
	return input.size() == 1 && (int(input[0]) >= 49 && int(input[0]) <= 57);
}

int IGameMode::processPlayerInput(char(&field)[3][3], int turn, char playerSymbol)
{
	std::cout << "Next turn \"" << playerSymbol << "\":" << std::endl;

	std::string input = "";
	while (!validateInput(input)) {
		std::cout << ">";
		std::cin >> input;
		if (!validateInput(input)) {
			printf_s("Input must be a digit between 1-9. Try again:\n");
		}
	}

	return input[0] - '0';
}
