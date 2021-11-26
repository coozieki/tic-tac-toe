#include "Game.h"

namespace GameInfo
{
	std::map<int, char> symbols = {
		{ 0, 'X' },
		{ 1, 'O' }
	};

	char getSymbolForPlayer(int player) {
		return symbols[player];
	}
};

void Game::resetGame()
{
	turn = 0;
	winner = -1;
	gameover = false;
	memcpy(field, initialField, sizeof(field));
}

void Game::showMainMenu()
{
	console.clearScreen();

chooseOption:
	std::cout 
		<< "Main menu:" << std::endl 
		<< "1. Start single player game" << std::endl 
		<< "2. Start two players game" << std::endl 
		<< "0. Exit" << std::endl;

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
		console.clearScreen();

	chooseSymbolOption:
		std::cout 
			<< "Choose your symbol:" << std::endl 
			<< "1. " << GameInfo::getSymbolForPlayer(0) << std::endl 
			<< "2. " << GameInfo::getSymbolForPlayer(1) << std::endl;

		int playerChosenSymbol;
		std::cout << ">";
		try {
			std::cin >> playerChosenSymbol;

			if (playerChosenSymbol != 1 && playerChosenSymbol != 2) {
				throw std::exception();
			}
		}
		catch (int) {
			console.clearScreen();
			std::cout << "Wrong input. Try again." << std::endl;
			goto chooseSymbolOption;
		}

		delete(gameMode);
		gameMode = new SinglePlayerMode(playerChosenSymbol - 1);
		draw(NULL);
		break;
	case 2:
		delete(gameMode);
		gameMode = new TwoPlayerMode();
		draw(NULL);
		break;
	case 0:
		delete(gameMode);
		exit(0);
		break;
	default:
		console.clearScreen();
		std::cout << "Wrong input. Try again:" << std::endl;
		goto chooseOption;
		break;
	}
}

int Game::processInput()
{
	return gameMode->processInput(field, turn, getCurrentTurnSymbol());
}

void Game::update(int input)
{
	updateFieldCell(input);
	gameover = checkGameOver();
	turn++;
}

void Game::draw(int input)
{
	console.clearScreen();
	for (int i = 0; i < 3; i++) {
		std::cout << "-------------" << std::endl;
		std::cout << "| " << field[i][0] << " | " << field[i][1] << " | " << field[i][2] << " |" << std::endl;
	}
	std::cout << "-------------" << std::endl;
}

bool Game::wantsToStartAgain()
{
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
		delete(gameMode);
		return false;
	default:
		std::cout << "Wrong input. Try again." << std::endl;
		goto chooseOption;
	}
}

void Game::updateFieldCell(int input)
{
	field[input / 3][input % 3 - 1] = getCurrentTurnSymbol();
}

bool Game::checkGameOver()
{
	return checkVerticalLines() || checkHorizontalLines() || checkDiagonalLines() || (turn == 8);
}

bool Game::checkVerticalLines()
{
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

bool Game::checkHorizontalLines()
{
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

bool Game::checkDiagonalLines()
{
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

void Game::setWinner()
{
	winner = turn % 2;
}

void Game::displayResult()
{
	std::cout << "Game over! ";
	if (winner == -1) {
		std::cout << "Draw!";
	}
	else {
		std::cout << "Winner is \"" << GameInfo::getSymbolForPlayer(winner) << "\"!";
	}
	std::cout << std::endl;
}

char Game::getCurrentTurnSymbol()
{
	return GameInfo::getSymbolForPlayer(turn % 2);
}
