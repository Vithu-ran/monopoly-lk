#include "players.h"

void initializePlayers(Player players[]) {
    for(int i = 0; i < PLAYER_COUNT; i++) {
        players[i].id = i + 1;
        players[i].position = 0;
        players[i].cash = 30000;
    }
}

void movePlayer(Player *player, int steps) {
    player->position += steps;

    if(player->position >= BOARD_SIZE) {
        player->position %= BOARD_SIZE;
        player->cash += GO_REWARD;
    }
}