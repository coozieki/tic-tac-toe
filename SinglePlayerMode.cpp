#include "SinglePlayerMode.h"

SinglePlayerMode::SinglePlayerMode(int playerChosenSymbol)
{
    this->playerChosenSymbol = playerChosenSymbol;
}

int SinglePlayerMode::processInput(char(&field)[3][3], int turn, char playerSymbol)
{
    if (turn % 2 == playerChosenSymbol) {
        return processPlayerInput(field, turn, playerSymbol);
    }
    else {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);

        srand(time(NULL));

        int input;
        do {
            input = (rand() % 9) + 1;
        } while (int(field[input / 3][input % 3 - 1]) < 49 || int(field[input / 3][input % 3 - 1]) > 57);

		return input;
    }
}
