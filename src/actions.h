#ifndef ACTIONS_H
#define ACTIONS_H

#include "game.h"

void handleProperty(Game *game, Player *player);

void handleRailway(Game *game, Player *player);

void handleUtility(Game *game, Player *player);

void handleGoToJail(Game *game, Player *player);

void handleJail(Game *game, Player *player);

void handleFreeParking(Game *game, Player *player);

int ownsMonopoly(Game *game, Player *player, PropertyGroup group);

void constructHouse(Game *game, Player *player, Square *square);

int canBuildHouse(Game *game, Square *square);

#endif