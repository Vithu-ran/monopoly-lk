#ifndef FINANCE_H
#define FINANCE_H

#include "game.h"

int calculatePlayerAssets(Game *game, Player *player);

void handleIncomeTax(Game *game, Player *player);

void handleCommunityTax(Game *game, Player *player);

void handleAuction(Game *game, Square *square);

int canTakeLoan(Game *game, Player *player);

void handleBank(Game *game, Player *player);

void handleInsurance(Game *game, Player *player);

int canPlayerBid(Player *player);

int getAuctionBid(Game *game, Player *player, Square *square, int currentBid);

#endif