#include "board.h"

int main(void) {
    
    Square board[BOARD_SIZE];
    initializeBoard(board);
    printBoard(board);

    return 0;
}