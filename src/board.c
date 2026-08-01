#include <stdio.h>
#include "board.h"

//to avoid other files work with the original entries which should never be changed
static const Square BOARD_TEMPLATE[BOARD_SIZE] = {
    //index, name, type, group
    {0, "GO", GO, NO_GROUP}, // simpler than using the dot operator
    {1, "Pettah", PROPERTY, BROWN},
    {2, "Community Development Fund", EVENT, NO_GROUP},
    {3, "Maradana", PROPERTY, BROWN},
    {4, "Income Tax", TAX, NO_GROUP},
    {5, "Colombo Fort Railway Station", RAILWAY, NO_GROUP},
    {6, "Bambalapitiya", PROPERTY, LIGHT_BLUE},
    {7, "National Event Card", EVENT, NO_GROUP},
    {8, "Wellawatte", PROPERTY, LIGHT_BLUE},
    {9, "Mount Lavinia", PROPERTY, LIGHT_BLUE},
    {10, "Jail / Just Visiting", JAIL, NO_GROUP},
    {11, "Nugegoda", PROPERTY, PINK},
    {12, "Ceylon Electricity Board", UTILITY, NO_GROUP},
    {13, "Maharagama", PROPERTY, PINK},
    {14, "Kottawa", PROPERTY, PINK},
    {15, "Kandy Railway Station", RAILWAY, NO_GROUP},
    {16, "Negombo", PROPERTY, ORANGE},
    {17, "Sri Lanka Insurance", INSURANCE, NO_GROUP},
    {18, "Katunayake", PROPERTY, ORANGE},
    {19, "Ja-Ela", PROPERTY, ORANGE},
    {20, "Free Parking", FREE_PARKING, NO_GROUP},
    {21, "Kandy City", PROPERTY, RED},
    {22, "National Event Card", EVENT, NO_GROUP},
    {23, "Peradeniya", PROPERTY, RED},
    {24, "Katugastota", PROPERTY, RED},
    {25, "Galle Railway Station", RAILWAY, NO_GROUP},
    {26, "Galle Fort", PROPERTY, YELLOW},
    {27, "Unawatuna", PROPERTY, YELLOW},
    {28, "National Water Supply and Drainage Board", UTILITY, NO_GROUP},
    {29, "Hikkaduwa", PROPERTY, YELLOW},
    {30, "Go To Jail", GO_TO_JAIL, NO_GROUP},
    {31, "Jaffna Town", PROPERTY, GREEN},
    {32, "Nallur", PROPERTY, GREEN},
    {33, "Ceylinco Insurance", INSURANCE, NO_GROUP},
    {34, "Trincomalee", PROPERTY, GREEN},
    {35, "Jaffna Railway Station", RAILWAY, NO_GROUP},
    {36, "National Event Card", EVENT, NO_GROUP},
    {37, "Nuwara Eliya", PROPERTY, DARK_BLUE},
    {38, "Bank of Ceylon", BANK, NO_GROUP},
    {39, "Galle Face", PROPERTY, DARK_BLUE}
};

void initializeBoard(Square board[]) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        board[i] = BOARD_TEMPLATE[i];
    }
}

void printBoard(const Square board[]) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d %-35s\n", board[i].index, board[i].name);
    }
}