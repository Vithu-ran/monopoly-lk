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

int canPlayerBid(Player *player) {
    return player->bankrupt == 0;
}

int getAuctionBid(Game *game, Player *player, Square *square, int currentBid) {
    int nextBid = currentBid + 250;

    if(player->cash < nextBid) {
        return -1;
    }

    return nextBid;
}

void handleAuction(Game *game, Square *square) {
    printf("\nAuction started for %s.\n", square->name);

    int currentBid = square->purchasePrice / 2; // 50% of the current market value
    Player *highestBidder = NULL;

    printf("Starting Bid : LKR %d\n\n", currentBid);

    int eligibleBidders = 0;

    for (int i = 0; i < PLAYER_COUNT; i++) {
        Player *player = &game->players[i];

        if (!canPlayerBid(player)) {
            continue;
        }

        eligibleBidders++;

        int bid = getAuctionBid(game, player, square, currentBid);

        if (bid == -1) { // cash < bid amount
            printf("%s withdraws.\n", player->name);
        } else {
            currentBid = bid;
            highestBidder = player;

            printf("%s bids LKR %d.\n", player->name, currentBid);
        }
    }

    if (eligibleBidders == 0) { // no one is eligible for bidding
        printf("\nNo eligible bidders.\n");
        printf("%s remains with the bank.\n", square->name);

        return;
    }

    if (highestBidder == NULL) { // everybody withdraws
        printf("\nNobody placed a bid.\n");
        printf("%s remains with the bank.\n", square->name);

        return;
    }

    printf("\nHighest Bid So Far\n");
    printf("%s : LKR %d\n", highestBidder->name, currentBid);

    //completing the transaction
    highestBidder->cash -= currentBid;
    square->owner = highestBidder->id;

    printf("\n%s purchased %s through auction.\n", highestBidder->name, square->name);
    printf("Remaining Balance : LKR %d\n", highestBidder->cash);
}

int canTakeLoan(Game *game, Player *player) {
    if(player->loan.active) {
        return 0;
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        Square *square = &game->board[i];

        if(square->owner == player-> id && (square->type == PROPERTY || square->type == RAILWAY || square->type == UTILITY)) {
            return 1;
        }
    }

    return 0;
}

int calculateMaximumLoan(Game *game, Player *player){
    int collateralValue = 0;

    for(int i = 0; i < BOARD_SIZE; i++) {
        Square *square = &game->board[i];

        if(square->owner != player->id) {
            continue;
        }

        if(square->type != PROPERTY && square->type != RAILWAY && square->type != UTILITY) {
            continue;
        }

        collateralValue += square->purchasePrice;
    }

    return (collateralValue * 75) / 100; // 75% of the collateral velue (later this will be changed to the mortgage value)
}

int getInterestRate(EconomicCondition condition) {
    switch(condition) {
        case ECONOMIC_BOOM:
            return 5;

        case STABLE_ECONOMY:
            return 8;

        case MODERATE_INFLATION:
            return 10;

        case HIGH_INFLATION:
            return 12;

        case ECONOMIC_RECESSION:
            return 15;

        default:
            return 8;
    }
}

void takeLoan(Game *game, Player *player) {
    if(!canTakeLoan(game, player)) {
        printf("%s is not eligible for the loan.\n", player->name);
        return;
    }

    int maximumLoan = calculateMaximumLoan(game, player);

    if(maximumLoan <= 0) {
        printf("%s has indufficient collateral for a loan.\n", player->name);
        return;
    }

    player->loan.amount = maximumLoan;
    player->loan.interestRate = getInterestRate(game->economicCondition);
    player->loan.roundsRemaining = 20;
    player->loan.active = 1;

    player->cash += maximumLoan;

    printf("%s borrowed LKR %d.\n", player->name, maximumLoan);
    printf("Loan period: %d rounds.\n", player->loan.roundsRemaining);
    printf("Remaining Cash: LKR %d.\n", player->cash);
}

int calculateLoanInterest(Player *player) {
    if(!player->loan.active) {
        return 0;
    }

    return (player->loan.amount * player->loan.interestRate) / 100;
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