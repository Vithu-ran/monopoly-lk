#include "players.h"

void initializePlayers(Player players[]) {
    for(int i = 0; i < PLAYER_COUNT; i++) {
        players[i].id = i + 1;
        players[i].position = 0;
        players[i].cash = 30000;
    }
    players[0].name = "Aggressive Investor";
    players[1].name = "Conservative Banker";
    players[2].name = "Risk Taker";
    players[3].name = "Opportunistic Trader";
}

void movePlayer(Player *player, int steps) {
    int newPosition = player->position + steps;

    if(newPosition >= BOARD_SIZE) {
        player->cash += GO_REWARD;
    }

    player->position = newPosition % BOARD_SIZE;
}