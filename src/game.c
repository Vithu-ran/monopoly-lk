#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void initializeGame(Game *game) {
    initializeBoard(game->board);
    initializePlayers(game->players);
}

void printIntroduction(const Game *game) { // const - to void accidental edits
    printf("\nMONOPOLY-LK Simulation\n\n");
    for(int i = 0; i < PLAYER_COUNT; i++) {
        printf("Player %d : %s\n", i + 1, game->players[i].name);
    }
    printf("\nEach player begins with LKR %d.\n\n", game->players[0].cash);
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
    int rolls[PLAYER_COUNT]; // stores everyonr's rolls

    // First rolling
    for(int i = 0; i < PLAYER_COUNT; i++) {
        Dice dice = rollDice();
        rolls[i] = dice.total;

        printf("%s rolls %d.\n", game->players[i].name, dice.total);

        if(rolls[i] > highestRoll) {
            highestRoll = rolls[i];
            highestPlayer = i;
        }
    }

    // Tie check
    int tieCount = 0;
    int tiedPlayers[PLAYER_COUNT]; // Stores the indices of tied players

    for(int i = 0; i < PLAYER_COUNT; i++) { // checks if the highest number rolled twice
        if(rolls[i] == highestRoll) {
            tiedPlayers[tieCount] = i; // Adds tied players to the array
            tieCount++;
        }
    }

    while(tieCount > 1) {
        printf("\nHighest roll tied. Rerolling...\n");
        
        int previousTiedCount = tieCount;
        highestRoll = 0;

        // Reroll only tied players
        for(int i = 0; i < previousTiedCount; i++) {
            int tiedPlayerIndex = tiedPlayers[i];

            Dice dice = rollDice(); // Rerolling the tied players

            rolls[tiedPlayerIndex] = dice.total; // Adding new rolls

            printf("%s rerolls %d.\n", game->players[tiedPlayerIndex].name, dice.total);

            if(rolls[tiedPlayerIndex] > highestRoll) {
                highestRoll = rolls[tiedPlayerIndex];
                highestPlayer = tiedPlayerIndex;
            }
        }

        // counting ties again
        tieCount = 0;

        for(int i = 0; i < previousTiedCount; i++) { // only the players who rerolled
            int tiedPlayerIndex = tiedPlayers[i];

            if(rolls[tiedPlayerIndex] == highestRoll) {
                tiedPlayers[tieCount] = tiedPlayerIndex;
                tieCount++;
            }
        }
    }

    return highestPlayer;
}

void printTurnOrder(Game *game, int firstPlayer) {
    for(int i = 0; i < PLAYER_COUNT; i++) {
        int currentPlayer = (firstPlayer + i) % PLAYER_COUNT;

        printf("%s\n", game->players[currentPlayer].name);
    }
}

void playGame(Game *game) {

    printIntroduction(game);

    printf("Rolling...\n\n");
    int firstPlayer = determineFirstPlayer(game);
    printf("\n%s will begin the game.\n", game->players[firstPlayer].name);

    printf("\nTurn order:\n");
    printTurnOrder(game, firstPlayer);
}