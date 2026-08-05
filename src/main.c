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

    game.board[1].owner = 0;
    game.board[3].owner = 0;

    constructHouse(&game, &game.players[0], &game.board[1]);


#else 

    playGame(&game);

#endif

    // playGame(&game);

    return 0;
}