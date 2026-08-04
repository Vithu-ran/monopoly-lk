#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"

void initializeGame(Game *game) {
    initializeBoard(game->board);
    initializePlayers(game->players);

    game->incomeTaxRate = 15; // percentage
    game->communityTaxRate = 10; // percentage
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
            printf("This is an Event square.\n");
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
            printf("This is a Bank.\n");
            break;

        case INSURANCE:
            printf("This is a Insurance Company.\n");
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

void handleProperty(Game *game, Player *player) {
    Square *square = &game->board[player->position];

    if(square->owner == -1) {
        if (player->cash >= square->purchasePrice) {
            player->cash -= square->purchasePrice;
            square->owner = player->id;
            
            printf("%s purchased %s for LKR %d.\n", player->name, square->name, square->purchasePrice);
            printf("Remaining Balance: LKR %d.\n", player->cash);
        } else {
            printf("%s cannot afford %s.\n",player->name, square->name);
            handleAuction(game, square); // to be implemented later
        }
    } else {
        if(square->owner == player->id) {
            printf("%s already owns %s.\n", player->name, square->name);
        } else {
            int rent = square->baseRent;

            printf("%s is owned by another player.\n", square->name);

            Player *owner = &game->players[square->owner]; // we can directly write owner->name without searching through all players
            player->cash -= rent;
            owner->cash += rent;

            printf("%s paid LKR %d to %s.\n", player->name, rent, owner->name);
            printf("%s Balance: LKR %d\n", player->name, player->cash);
            printf("%s Balance: LKR %d\n", owner->name, owner->cash);
        }
    }
}

void handleRailway(Game *game, Player *player) {
    Square *square = &game->board[player->position];

    if(square->owner == -1) {
        if(player->cash > square->purchasePrice) {
            player->cash -= square->purchasePrice;
            square->owner = player->id;

            printf("%s purchased %s for LKR %d.\n", player->name, square->name, square->purchasePrice);
            printf("Remaining Balance: LKR %d.\n", player->cash);
        } else {
            printf("%s cannot afford %s.\n",player->name, square->name);
            handleAuction(game, square);
        }
    } else {
        if(square->owner == player->id) {
            printf("%s already owns %s.\n", player->name, square->name);
        } else {
            printf("%s is owned by another player.\n", square->name);

            int railwayCount = 0; // how many railways does that particular player own

            for(int i = 0; i < BOARD_SIZE; i++) {
                if(game->board[i].type == RAILWAY && game->board[i].owner == square->owner) {
                        railwayCount++;
                }
            }

            int railwayRent[] = {0, 250, 500, 1000, 2000}; // this is better than implementing a switch statement
            int rent = railwayRent[railwayCount];

            Player *owner = &game->players[square->owner]; // increases readability

            player->cash -= rent;
            owner->cash += rent;

            printf("%s paid LKR %d to %s.\n", player->name, rent, owner->name);
            printf("%s's Remaining Balance: LKR %d.\n", player->name, player->cash);
        }
    }
}

void handleUtility(Game *game, Player *player) {
        Square * square = &game->board[player->position];

        if(square->owner == -1) {
            if(player->cash > square->purchasePrice) {
                player->cash -= square->purchasePrice;
                square->owner = player->id;

                printf("%s purchased %s for LKR %d.\n", player->name, square->name, square->purchasePrice);
                printf("Remaining Balance: LKR %d.\n", player->cash);
            } else {
                printf("%s cannot afford %s.\n",player->name, square->name);
                handleAuction(game, square);
            }
        } else {
            if(square->owner == player->id) {
                printf("%s already owns %s.\n", player->name, square->name);
            } else {
                printf("%s is owned by another player.\n", square->name);

                Player *owner = &game->players[square->owner];

                int utilityCount = 0;
                for(int i = 0; i < BOARD_SIZE; i++) {
                    if(game->board[i].type = UTILITY && game->board[i].owner == owner->id) {
                        utilityCount++;
                    }
                }
                
                int multiplier;
                if(utilityCount == 1) {
                    multiplier = 4;
                } else {
                    multiplier = 10;
                }

                int rent = player->lastDiceRoll * multiplier;

                player->cash -= rent;
                owner->cash += rent;

                printf("%s paid LKR %d to %s.\n", player->name, rent, owner->name);
                printf("%s's Remaining Balance: LKR %d.\n", player->name, player->cash);
            }
        }
}

void handleAuction(Game *game, Square *square) {
    printf("%s is going to auction.\n", square->name); // LATER
}

int calculatePlayerAssets(Game *game, Player *player) {

    int assets = player->cash;

    for(int i = 0; i < BOARD_SIZE; i++) {

        Square *square = &game->board[i];

        if(square->owner == player->id  && (square->type == PROPERTY || square->type == RAILWAY || square->type == UTILITY)) {
            assets += square->purchasePrice; // will be replaced after implementiong the market conditions
        }
    }
    
    return assets;
}

void handleIncomeTax(Game *game, Player *player) {
    int assets = calculatePlayerAssets(game, player);

    int tax = (assets * game->incomeTaxRate) / 100;

    printf("Total Assets : LKR %d\n", assets);
    printf("Income Tax (%d%%) : LKR %d\n", game->incomeTaxRate, tax);

    if(player->cash >= tax) {
        player->cash -= tax;
        
        printf("%s paid LKR %d as Income Tax.\n", player->name, tax);
        printf("Remaining Balance: LKR %d\n", player->cash);
    } else {
        printf("%s cannot pay Income Tax.\n", player->name);
        // the amount will be added to debt (implemented later)
    }
}

void handleCommunityTax(Game *game, Player *player) {
    int assets = calculatePlayerAssets(game, player);

    int tax = (assets * game->communityTaxRate) / 100;

    printf("Total Assets : LKR %d\n", assets);
    printf("Community Development Fund (%d%%) : LKR %d\n", game->communityTaxRate, tax);

    if(player->cash >= tax) {
        player->cash -= tax;
        
        printf("%s paid LKR %d as Income Tax.\n", player->name, tax);
        printf("Remaining Balance: LKR %d\n", player->cash);
    } else {
        printf("%s cannot pay Community Development Fund.\n", player->name);
        // the amount will be added to debt (implemented later)
    }
}

void handleGoToJail(Game *game, Player *player) {
    player->position = JAIL_INDEX;
    printf("%s was sent directly to Jail.\n", player->name);
}

void handleJail(Game *game, Player *player) {
    printf("%s is Just Visiting Jail.\n", player->name);
}

void handleFreeParking(Game *game, Player *player) {
    printf("%s is taking a break at Free Parking.\n", player->name);
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