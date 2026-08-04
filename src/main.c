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

    // game.players[0].cash = 1000;

    // game.board[1].owner = 0;
    // game.board[11].owner = 0;
    // game.board[37].owner = 0;

    // game.players[0].position = 17;
    game.players[0].position = 33;
    // game.players[0].position = 38;

    handleInsurance(&game, &game.players[0]);


#else 

    playGame(&game);

#endif

    // playGame(&game);

    return 0;
}