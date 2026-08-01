#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "board.h"
#include "players.h"

typedef struct {
    Square board[BOARD_SIZE]; // Every game has its own board
    Player players[PLAYER_COUNT];
} Game;

void initializeGame(Game *game);
/* POIINTER
to avoid unneessary copying
the game attributes must be changing throughout the game
so the modifications remain even after the function ends
*/

Dice rollDice(void); //A funtion that returns Dice structure

void playGame(Game *game);

#endif