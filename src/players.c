#include "players.h"
#include "types.h"

void initializePlayers(Player players[]) {
    for(int i = 0; i < PLAYER_COUNT; i++) {
        players[i].id = i;
        players[i].position = 0;
        players[i].cash = 30000;
        players[i].bankrupt = 0; // 1 = player bankrupted
        players[i].loan.amount = 0; // because no loand exist at the beginning
        players[i].loan.interestRate = 0;
        players[i].loan.roundsRemaining = 0;
        players[i].loan.active = 0;
    }
    players[0].name = "Aggressive Investor";
    players[1].name = "Conservative Banker";
    players[2].name = "Risk Taker";
    players[3].name = "Opportunistic Trader";


}

void movePlayer(Player *player, int steps) { // updating the player's state only
    int newPosition = player->position + steps;

    if(newPosition >= BOARD_SIZE) {
        player->cash += GO_REWARD;
    }

    player->position = newPosition % BOARD_SIZE;
}