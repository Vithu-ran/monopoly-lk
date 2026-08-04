#ifndef FINANCE_H
#define FINANCE_H

#include "game.h"

int calculatePlayerAssets(Game *game, Player *player);

void handleIncomeTax(Game *game, Player *player);

void handleCommunityTax(Game *game, Player *player);

void handleAuction(Game *game, Square *square);

#endif