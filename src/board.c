#include <stdio.h>
#include "board.h"

//to avoid other files work with the original entries which should never be changed
static const Square BOARD_TEMPLATE[BOARD_SIZE] = {
    //index, name, type, group, purchasePrice, baseRent, owner, houses, hotel, houseCost, hotelCost
    {0, "GO", GO, NO_GROUP, 0, 0, -1, 0, 0, 0, 0}, // simpler than using the dot operator
    {1, "Pettah", PROPERTY, BROWN, 1500, 100, -1, 0, 0, 500, 2000},
    {2, "Community Development Fund", COMMUNITY_DEVELOPMENT_FUND, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {3, "Maradana", PROPERTY, BROWN, 1800, 120, -1, 0, 0, 500, 2000},
    {4, "Income Tax", INCOME_TAX, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {5, "Colombo Fort Railway Station", RAILWAY, NO_GROUP, 1500, 0, -1, 0, 0, 0, 0},
    {6, "Bambalapitiya", PROPERTY, LIGHT_BLUE, 2500, 180, -1, 0, 0, 750, 3000},
    {7, "National Event Card", EVENT, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {8, "Wellawatte", PROPERTY, LIGHT_BLUE, 2700, 200, -1, 0, 0, 750, 3000},
    {9, "Mount Lavinia", PROPERTY, LIGHT_BLUE, 3000, 220, -1, 0, 0, 750, 3000},
    {10, "Jail (Just visiting)", JAIL, NO_GROUP, 0, 0, -1, 0, 0, 0, 0}, // Special type = JAIL
    {11, "Nugegoda", PROPERTY, PINK, 3500, 260, -1, 0, 0, 1000, 4000},
    {12, "Ceylon Electricity Board", UTILITY, NO_GROUP, 1500, 0, -1, 0, 0, 0, 0},
    {13, "Maharagama", PROPERTY, PINK, 3800, 280, -1, 0, 0, 1000, 4000},
    {14, "Kottawa", PROPERTY, PINK, 4000, 300, -1, 0, 0, 1000, 4000},
    {15, "Kandy Railway Station", RAILWAY, NO_GROUP, 1500, 0, -1, 0, 0, 0, 0},
    {16, "Negombo", PROPERTY, ORANGE, 4500, 350, -1, 0, 0, 1250, 5000},
    {17, "Sri Lanka Insurance", INSURANCE, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {18, "Katunayake", PROPERTY, ORANGE, 4700, 370, -1, 0, 0, 1250, 5000},
    {19, "Ja-Ela", PROPERTY, ORANGE, 5000, 400, -1, 0, 0, 1250, 5000},
    {20, "Free Parking", FREE_PARKING, NO_GROUP, 0, 0, -1, 0, 0, 0, 0}, // Special type = FREE_PARKING
    {21, "Kandy City", PROPERTY, RED, 5500, 450, -1, 0, 0, 1500, 6000},
    {22, "National Event Card", EVENT, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {23, "Peradeniya", PROPERTY, RED, 5800, 480, -1, 0, 0, 1500, 6000},
    {24, "Katugastota", PROPERTY, RED, 6000, 500, -1, 0, 0, 1500, 6000},
    {25, "Galle Railway Station", RAILWAY, NO_GROUP, 1500, 0, -1, 0, 0, 0, 0},
    {26, "Galle Fort", PROPERTY, YELLOW, 6500, 600, -1, 0, 0, 2000, 8000},
    {27, "Unawatuna", PROPERTY, YELLOW, 6800, 620, -1, 0, 0, 2000, 8000},
    {28, "National Water Supply and Drainage Board", UTILITY, NO_GROUP, 1500, 0, -1, 0, 0, 0, 0},
    {29, "Hikkaduwa", PROPERTY, YELLOW, 7000, 650, -1, 0, 0, 2000, 8000},
    {30, "Go To Jail", GO_TO_JAIL, NO_GROUP, 0, 0, -1, 0, 0, 0, 0}, // Special type = GO_TO_JAIL
    {31, "Jaffna Town", PROPERTY, GREEN, 8000, 750, -1, 0, 0, 2500, 10000},
    {32, "Nallur", PROPERTY, GREEN, 8300, 780, -1, 0, 0, 2500, 10000},
    {33, "Ceylinco Insurance", INSURANCE, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {34, "Trincomalee", PROPERTY, GREEN, 8500, 800, -1, 0, 0, 2500, 10000},
    {35, "Jaffna Railway Station", RAILWAY, NO_GROUP, 1500, 0, -1, 0, 0, 0, 0},
    {36, "National Event Card", EVENT, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {37, "Nuwara Eliya", PROPERTY, DARK_BLUE, 10000, 1000, -1, 0, 0, 3000, 12000},
    {38, "Bank of Ceylon", BANK, NO_GROUP, 0, 0, -1, 0, 0, 0, 0},
    {39, "Galle Face", PROPERTY, DARK_BLUE, 12000, 1200, -1, 0, 0, 3000, 12000}
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