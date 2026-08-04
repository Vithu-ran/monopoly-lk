#ifndef ACTIONS_H
#define ACTIONS_H

#include "game.h"

void handleProperty(Game *game, Player *player);

void handleRailway(Game *game, Player *player);

void handleUtility(Game *game, Player *player);

void handleGoToJail(Game *game, Player *player);

void handleJail(Game *game, Player *player);

void handleFreeParking(Game *game, Player *player);

#endif