#ifndef ROGUE_H
#define ROGUE_H
#endif
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
struct Position {
    int x;
    int y;
};
typedef struct Position Position;
typedef struct Position* pPosition;

struct Room {
    Position position;
    int height;
    int width;
    pPosition * door;
    //Monster ** monsters;
    //Item ** items;
};
typedef struct Room Room;
typedef struct Room* pRoom;

struct Player {
    Position position;
    int health;
};
typedef struct Player Player;
typedef struct Player* pPlayer;

int screenSetUp();
pRoom * mapSetUp();
int processInput(int ch, pPlayer user);
int playerMove(int y, int x, pPlayer user);
int checkPos(int newY, int newX, pPlayer user);
pPlayer playerSetUp();
pRoom createRoom(int x, int y, int height, int width);
int drawRoom(pRoom room);
int connectDoors(pPosition door1, pPosition door2);