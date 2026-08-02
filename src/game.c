#include <stdio.h>
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

// finding who starts the game
int determineFirstPlayer(Game *game) {
    int highestPlayer = 0;
    int highestRoll = 0;
    int rolls[PLAYER_COUNT];

    for(int i = 0; i < PLAYER_COUNT; i++) {
        Dice dice = rollDice();
        rolls[i] = dice.total;

        printf("%s rolls %d.\n", game->players[i].name, dice.total);

        if(rolls[i] > highestRoll) {
            highestRoll = rolls[i];
            highestPlayer = i;
        }
    }

    // Tie check is only for the firs rank
    int tieCount = 0;
    int tiedPlayers[PLAYER_COUNT];
    int tiedIndex = 0;

    for(int i = 0; i < PLAYER_COUNT; i++) { // checks if the highest number rolled twice
        if(rolls[i] == highestRoll) {
            tieCount++;
        }
    }

    while(tieCount > 1) {
        printf("\nHighest roll tied. Rerolling...\n");

        highestRoll = 0;
        tieCount = 0;
        tiedIndex = 0;

        // Reroll only tied players
        for(int i = 0; i < PLAYER_COUNT; i++) {
            if(rolls[i] == highestRoll) {
                // Nothing for now
            }
        }
    }

    return highestPlayer;
}

void playGame(Game *game) {
    int firstPlayer = determineFirstPlayer(game);

    // printf("\n%s will begin the game.\n", game->players[firstPlayer].name);
}