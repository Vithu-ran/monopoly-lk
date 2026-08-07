#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "actions.h"
#include "finance.h"
#include "events.h"

void initializeGame(Game *game) {
    initializeBoard(game->board);
    initializePlayers(game->players);

    game->incomeTaxRate = 15; // percentage
    game->communityTaxRate = 10; // percentage

    game->economicCondition = STABLE_ECONOMY;
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
        int currentPlayerIndex = (firstPlayer + i) % PLAYER_COUNT;

        printf("%s\n", game->players[currentPlayerIndex].name);
    }
}

// Handles a player's turn and output messages
void takeTurn(Game *game, Player *player) {
    printf("\n----------------------------------------\n");
    printf("%s's Turn\n", player->name);
    printf("----------------------------------------\n");

    Dice dice = rollDice();
    player->lastDiceRoll = dice.total;
    printf("%s rolled %d.\n", player->name, dice.total);

    int oldPosition = player->position;

    movePlayer(player, dice.total);

    printf("%s moves from Square %d to Square %d.\n", player->name, oldPosition, player->position);

    if(player->position < oldPosition) {
        printf("%s passed GO.\n", player->name);
        printf("Collected LKR %d.\n", GO_REWARD);
        printf("Current Balance : LKR %d.\n", player->cash);
    }
}

void handleLanding(Game *game, Player *player) {
    Square *square = &game->board[player->position];

    printf("\n%s landed on %s.\n", player->name, square->name);

    switch(square->type) {
        case GO:
            break;

        case PROPERTY:
            handleProperty(game, player);
            break;
        
        case RAILWAY:
            handleRailway(game, player);
            break;

        case EVENT:
            handleEvents(game, player);
            break;

        case INCOME_TAX:
            handleIncomeTax(game, player);
            break;

        case COMMUNITY_DEVELOPMENT_FUND:
            handleCommunityTax(game, player);
            break;

        case UTILITY:
            handleUtility(game, player);
            break;

        case BANK:
            handleBank(game, player);
            break;

        case INSURANCE:
            handleInsurance(game, player);
            break;

        case JAIL:
            handleJail(game, player);
            break;

        case FREE_PARKING:
            handleFreeParking(game, player);
            break;

        case GO_TO_JAIL:
            handleGoToJail(game, player);
            break;

        default:
            printf("Unknown square type.\n")    ;
            break;
    }
}

void playGame(Game *game) {

    printIntroduction(game);

    printf("Rolling...\n\n");
    int firstPlayer = determineFirstPlayer(game);
    printf("\n%s will begin the game.\n", game->players[firstPlayer].name);

    printf("\nTurn order:\n");
    printTurnOrder(game, firstPlayer);

    for(int i = 0; i < PLAYER_COUNT; i++) {
        int currentPlayerIndex = (firstPlayer + i) % PLAYER_COUNT;

        takeTurn(game, &game->players[currentPlayerIndex]);
        handleLanding(game, &game->players[currentPlayerIndex]);
    }
}