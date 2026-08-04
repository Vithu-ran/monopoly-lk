#include <stdio.h>
#include "actions.h"
#include "finance.h"

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
            handleAuction(game, square); // to be implemented
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
            handleAuction(game, square); // will be implemented
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