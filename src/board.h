#ifndef BOARD_H
#define BOARD_H

#include "types.h"

void initializeBoard(Square board[]);
void printBoard(const Square board[]); //const - to avoid modifying the board

#endif