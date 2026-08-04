#ifndef TYPES_H
#define TYPES_H

#define PLAYER_COUNT 4
#define BOARD_SIZE 40
#define GO_REWARD 2000
#define JAIL_INDEX 10

typedef enum {
    GO,
    PROPERTY,
    EVENT,
    INCOME_TAX,
    COMMUNITY_DEVELOPMENT_FUND,
    RAILWAY,
    UTILITY,
    BANK,
    INSURANCE,
    JAIL,
    FREE_PARKING,
    GO_TO_JAIL
} SquareType;

typedef enum {
    NO_GROUP,
    BROWN,
    LIGHT_BLUE,
    PINK,
    ORANGE,
    RED,
    YELLOW,
    GREEN,
    DARK_BLUE
} PropertyGroup;

typedef struct {
    int id;
    char *name;
    int position;
    int cash;
    int lastDiceRoll;
    int bankrupt;
} Player;

typedef struct {
    int index;
    char name[40];
    SquareType type;
    PropertyGroup group;
    int purchasePrice;
    int baseRent;
    int owner;
    int houses;
    int hotel;
} Square;

typedef struct {
    int dice1;
    int dice2;
    int total;
} Dice;

#endif