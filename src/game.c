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

int determineFirstPlayer(Game *game) {
    int highestPlayer = 0;
    int highestRoll = 0;

    for(int i = 0; i < PLAYER_COUNT; i++) {
        Dice dice = rollDice();

        printf("%s rolls %d.\n", game->players[i].name, dice.total);

        if(dice.total > highestRoll) {
            highestRoll = dice.total;
            highestPlayer = i;
        }
    }

    return highestPlayer;
}

void playGame(Game *game) {
    // for(int i = 0; i < PLAYER_COUNT; i++) { //temporary because the turn order isn't fixed
    //     Dice dice = rollDice();

    //     printf("%s rolled %d.\n", game->players[i].name, dice.total);

    //     movePlayer(&game->players[i], dice.total);

    //     printf("%s is now on Square %d.\n\n", game->players[i].name, game->players[i].position);
    // }

    int firstPlayer = determineFirstPlayer(game);

    printf("\n%s will begin the game.\n", game->players[firstPlayer].name);
}