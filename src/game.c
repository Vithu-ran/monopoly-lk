#include <stdlib.h>
#include "game.h"

void initializeGame(Game *game) {
    initializeBoard(game->board);
    initializePlayers(game->players);
}

Dice rollDice(void) {
    Dice dice;

    dice.dice1 = rand() % 6 + 1;
    dice.dice2 = rand() % 6 + 1;
    dice.total = dice.dice1 + dice.dice2;

    return dice;
}