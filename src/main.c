#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"

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

    game.players[0].position = 30;

    handleGoToJail(&game, &game.players[0]);

    printf("index - %d\n", game.players[0].position);
    // printf("Cash: %d\n", game.players[0].cash);

    // handleIncomeTax(&game, &game.players[0]);

#else 

    playGame(&game);

#endif

    // playGame(&game);

    return 0;
}