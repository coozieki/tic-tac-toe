#include <iostream>
#include <memory.h>
#include <map>

class Console
{
public:
	void clearScreen()
	{
		#if defined _WIN32
				system("cls");
				//clrscr(); // including header file : conio.h
		#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
				system("clear");
				//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
		#elif defined (__APPLE__)
				system("clear");
		#endif
	}
};

class Game 
{
private:
	bool gameover = false;

	const char initialField[3][3] = {
		{ '1', '2', '3' },
		{ '4', '5', '6' },
		{ '7', '8', '9' }
	};

	char field[3][3] = {
		{ '1', '2', '3' },
		{ '4', '5', '6' },
		{ '7', '8', '9' }
	};

	int turn = 0;

	int winner = -1;

	Console console = Console();

	std::map<int, char> symbols = {
		{ 0, 'X' },
		{ 1, 'O' }
	};

	void resetGame() {
		turn = 0;
		winner = -1;
		gameover = false;
		memcpy(field, initialField, sizeof(field));
	}

	void showMainMenu() {
		console.clearScreen();

	chooseOption:
		std::cout << "Main menu:" << std::endl << "1. Start new game" << std::endl << "0. Exit" << std::endl;

		int input;
		try {
			std::cout << ">";
			std::cin >> input;
		}
		catch (int) {
			console.clearScreen();
			std::cout << "Wrong input. Try again:" << std::endl;
			goto chooseOption;
		}

		switch (input) {
		case 1:
			draw(NULL);
			break;
		case 0:
			exit(0);
			break;
		default:
			console.clearScreen();
			std::cout << "Wrong input. Try again:" << std::endl;
			goto chooseOption;
			break;
		}
	}

	int processInput() {
		std::cout << "Next turn \"" << getCurrentTurnSymbol() << "\":" << std::endl;

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

	void update(int input) {
		updateFieldCell(input);
		gameover = checkGameOver();
		turn++;
	}

	void draw(int input) {
		console.clearScreen();
		for (int i = 0; i < 3; i++) {
			std::cout << "-------------" << std::endl;
			std::cout << "| " << field[i][0] << " | " << field[i][1] << " | " << field[i][2] << " |" << std::endl;
		}
		std::cout << "-------------" << std::endl;
	}

	bool wantsToStartAgain() {
	chooseOption:
		std::cout << "Want to start again?" << std::endl << "1. Yes" << std::endl << "2. No" << std::endl;

		int input;
		try {
			std::cout << ">";
			std::cin >> input;
		}
		catch (int) {
			std::cout << "Wrong input. Try again." << std::endl;
			goto chooseOption;
		}

		switch (input) {
		case 1:
			return true;
		case 2:
			return false;
		default:
			std::cout << "Wrong input. Try again." << std::endl;
			goto chooseOption;
		}
	}

	void updateFieldCell(int input) {
		field[input / 3][input % 3 - 1] = getCurrentTurnSymbol();
	}

	bool checkGameOver() {
		return checkVerticalLines() || checkHorizontalLines() || checkDiagonalLines() || (turn == 8);
	}

	bool checkVerticalLines() {
		char prevChar = NULL;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (prevChar == NULL) {
					prevChar = field[j][i];
					continue;
				}

				if (prevChar != field[j][i] || (prevChar != 'X' && prevChar != 'O')) {
					prevChar = NULL;
					break;
				}

				if (j == 2) {
					setWinner();
					return true;
				}
			}
		}

		return false;
	}

	bool checkHorizontalLines() {
		char prevChar = NULL;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (prevChar == NULL) {
					prevChar = field[i][j];
					continue;
				}

				if (prevChar != field[i][j] || (prevChar != 'X' && prevChar != 'O')) {
					prevChar = NULL;
					break;
				}

				if (j == 2) {
					setWinner();
					return true;
				}
			}
		}

		return false;
	}

	bool checkDiagonalLines() {
		char prevChar = NULL;

		for (int i = 0; i < 3; i++) {
			if (prevChar == NULL) {
				prevChar = field[i][i];
				continue;
			}

			if (prevChar != field[i][i] || (prevChar != 'X' && prevChar != 'O')) {
				break;
			}

			if (i == 2) {
				setWinner();
				return true;
			}
		}

		prevChar = NULL;
		for (int i = 2; i >= 0; i--) {
			if (prevChar == NULL) {
				prevChar = field[i][2 - i];
				continue;
			}

			if (prevChar != field[i][2 - i] || (prevChar != 'X' && prevChar != 'O')) {
				break;
			}

			if (i == 0) {
				setWinner();
				return true;
			}
		}

		return false;
	}

	bool validateInput(std::string input) {
		return input.size() == 1 && (int(input[0]) >= 49 && int(input[0]) <= 57);
	}

	void setWinner() {
		winner = turn % 2;
	}

	void displayResult() {
		std::cout << "Game over! ";
		if (winner == -1) {
			std::cout << "Draw!";
		}
		else {
			std::cout << "Winner is \"" << symbols[winner] << "\"!";
		}
		std::cout << std::endl;
	}

	char getCurrentTurnSymbol() {
		return symbols[turn % 2];
	}

public:

	void start() {
	newGame:
		resetGame();
		showMainMenu();

		while (!gameover) {
			int input = processInput();
			update(input);
			draw(input);
		}

		displayResult();
		if (wantsToStartAgain()) {
			goto newGame;
		}
	}
};

int main()
{
	Game game = Game();
	game.start();
	return 0;
}
