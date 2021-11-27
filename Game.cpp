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
	delete(gameMode);
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

	std::string input;

	std::cout << ">";
	std::cin >> input;

	if (input != "1" && input != "2" && input != "0") {
		console.clearScreen();
		std::cout << "Wrong input. Try again:" << std::endl;
		goto chooseOption;
	}

	std::string playerChosenSymbol;

	switch (input[0]) {
	case '1':
		console.clearScreen();

	chooseSymbolOption:
		std::cout 
			<< "Choose your symbol:" << std::endl 
			<< "1. " << GameInfo::getSymbolForPlayer(0) << std::endl 
			<< "2. " << GameInfo::getSymbolForPlayer(1) << std::endl;


		std::cout << ">";
		std::cin >> playerChosenSymbol;

		if (playerChosenSymbol != "1" && playerChosenSymbol != "2") {
			console.clearScreen();
			std::cout << "Wrong input. Try again." << std::endl;
			goto chooseSymbolOption;
		}

		gameMode = new SinglePlayerMode(playerChosenSymbol[0] - '0' - 1);
		break;
	case '2':
		gameMode = new TwoPlayerMode();
		break;
	case '0':
		exit(0);
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
	std::cout << "Want to start again?" << std::endl << "1. Yes" << std::endl << "2. No" << std::endl;

	std::string input;

chooseOption:
	std::cout << ">";
	std::cin >> input;

	if (input != "1" && input != "2") {
		std::cout << "Wrong input. Try again:" << std::endl;
		goto chooseOption;
	}

	return input == "1" ? true : false;
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
	bool gameover = (field[0][0] == field[1][0] && field[1][0] == field[2][0])
				 || (field[0][1] == field[1][1] && field[1][1] == field[2][1])
				 || (field[0][2] == field[1][2] && field[1][2] == field[2][2]);

	if (gameover) setWinner();

	return gameover;
}

bool Game::checkHorizontalLines()
{
	bool gameover = (field[0][0] == field[0][1] && field[0][1] == field[0][2])
				 || (field[1][0] == field[1][1] && field[1][1] == field[1][2])
				 || (field[2][0] == field[2][1] && field[2][1] == field[2][2]);

	if (gameover) setWinner();

	return gameover;
}

bool Game::checkDiagonalLines()
{
	bool gameover = (field[0][0] == field[1][1] && field[1][1] == field[2][2])
				 || (field[2][0] == field[1][1] && field[1][1] == field[0][2]);

	if (gameover) setWinner();

	return gameover;
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

void Game::start()
{
newGame:
	resetGame();
	showMainMenu();

	draw(NULL);
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
