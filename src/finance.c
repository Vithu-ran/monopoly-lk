#include <stdio.h>
#include "finance.h"

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

void handleAuction(Game *game, Square *square) {
    printf("%s is going to auction.\n", square->name); // LATER
}

void handleBank(Game *game, Player *player) {
    printf("%s arrived at the Bank.\n", player->name);
    printf("Banking services are available.\n");

    // banking operations will be implemented
}

void handleInsurance(Game *game, Player *player) {
    printf("%s arrived at the Insurance.\n", player->name);
    printf("Insurance services are available.\n");

    // insurance operations will be implemented
}