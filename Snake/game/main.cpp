#include "SnakeGame.h"

int main(void)
{
    SnakeGame game;
    game.Main();

    return 0;
}

/*
9x16 mobile UI
magic fruit = controls your char for 10 seconds using AStar. Each movement you need to run the AStar again.
*/