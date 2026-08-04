#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "board.h"
#include "players.h"

typedef struct {
    Square board[BOARD_SIZE]; // Every game has its own board
    Player players[PLAYER_COUNT];
    int turnOrder[PLAYER_COUNT]; // Stores index of the players array
    int incomeTaxRate; // percentage
    int communityTaxRate; //percentage
} Game;


void initializeGame(Game *game);
/* POIINTER
to avoid unneessary copying
the game attributes must be changing throughout the game
so the modifications remain even after the function ends
*/

void printIntroduction(const Game *game);

Dice rollDice(void); //A funtion that returns Dice structure

int determineFirstPlayer(Game *game); // returning the index of the first player

void printTurnOrder(Game *game, int firstPlayer);

void takeTurn(Game *game, Player *player);

void handleLanding(Game *game, Player *player);

void handleProperty(Game *game, Player *player);

void handleRailway(Game *game, Player *player);

void handleUtility(Game *game, Player *player);

void handleAuction(Game *game, Square *square);

int calculatePlayerAssets(Game *game, Player *player);

void handleIncomeTax(Game *game, Player *player);

void handleCommunityTax(Game *game, Player *player);

void handleGoToJail(Game *game, Player *player);

void handleJail(Game *game, Player *player);

void playGame(Game *game);

#endif