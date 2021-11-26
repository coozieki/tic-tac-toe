#include "TwoPlayerMode.h"

int TwoPlayerMode::processInput(char(&field)[3][3], int turn, char playerSymbol)
{
	return processPlayerInput(field, turn, playerSymbol);
}
