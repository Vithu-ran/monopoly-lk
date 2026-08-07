#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"
#include "events.h"
#include "actions.h"
#include "finance.h"
#include "players.h"

#define TEST_MODE 0

int main(void) {
    
    srand(time(NULL)); //to avoid getting the same sequence
    
    Game game;

    initializeGame(&game);

#if TEST_MODE

    game.players[0].cash = 20000;
    game.players[0].loan.active = 1;
    game.players[0].loan.amount = 10000;
    game.players[0].loan.interestRate = 8;

    repayLoan(&game.players[0], 3000);

    printf("%d, %d\n", game.players[0].cash, game.players[0].loan.amount);

#else 

    playGame(&game);

#endif

    // playGame(&game);

    return 0;
}