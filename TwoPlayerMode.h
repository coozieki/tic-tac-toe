#pragma once

#include <iostream>

#include "IGameMode.h"

class TwoPlayerMode : public IGameMode
{
public:
	virtual int processInput(char(&field)[3][3], int turn, char playerSymbol);
};