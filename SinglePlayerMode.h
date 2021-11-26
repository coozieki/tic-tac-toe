#pragma once

#include <time.h>
#include <chrono>
#include <thread>

#include "IGameMode.h"

class SinglePlayerMode :
    public IGameMode
{
private:
    int playerChosenSymbol;

public:
    SinglePlayerMode(int playerChosenSymbol);

    virtual int processInput(char(&field)[3][3], int turn, char playerSymbol) override;
};

