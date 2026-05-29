#include "SnakeGame.h"

int main(void)
{
    SnakeGame game;
    game.Main();

    return 0;
}

/*
  Allow the game to be played in any width/height
  Make sure the enw spawned pickup (fruit) is not anywhere on the player
  Make sure if the player loops back on itself, thegame is over
  When the game is over, have a way to re-start the game
  If the tail becomes too long that cover the whole screen, stop the game
 
  put everything into a nice repo with an animation
*/