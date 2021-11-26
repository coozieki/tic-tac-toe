#pragma once

#include <iostream>
#include <memory.h>
#include <map>

#include "Console.h"
#include "IGameMode.h"
#include "TwoPlayerMode.h"
#include "SinglePlayerMode.h"

class Game
{
private:
	Console console = Console();

	IGameMode* gameMode;

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

	void resetGame();

	void showMainMenu();



	int processInput();

	void update(int input);

	void draw(int input);



	void displayResult();

	bool wantsToStartAgain();



	void updateFieldCell(int input);

	bool checkGameOver();

	bool checkVerticalLines();

	bool checkHorizontalLines();

	bool checkDiagonalLines();

	void setWinner();

	char getCurrentTurnSymbol();

public:

	void start();
};