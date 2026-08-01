#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"

int main(void) {
    
    srand(time(NULL)); //to avoid getting the same sequence
    
    Game game;
    initializeGame(&game);
    
    Dice dice = rollDice();

    printf("Dice 1 : %d\n", dice.dice1);
    printf("Dice 2 : %d\n", dice.dice2);
    printf("Total  : %d\n", dice.total);

    return 0;
}