#pragma once

#include <iostream>

class IGameMode
{
protected:
	bool validateInput(std::string input);

	int processPlayerInput(char (&field)[3][3], int turn, char playerSymbol);

public:
	virtual int processInput(char (&field)[3][3], int turn, char playerSymbol) = 0;
};