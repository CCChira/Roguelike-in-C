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
int main() {
    pPlayer user;
    int ch;
    screenSetUp();

    mapSetUp();

    user = playerSetUp();
    /////////////////   SET UP ///////////////////
    while((ch = getch()) != 'q') {
        processInput(ch, user);
    }
    getch();
    endwin();
    return 0;
}

pPlayer playerSetUp() {
    pPlayer newPlayer = (pPlayer)malloc(sizeof(Player));
    if(newPlayer != NULL) {
        newPlayer->position.x = 14;
        newPlayer->position.y = 14;
        newPlayer->health = 20;
        mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
        move(newPlayer->position.y, newPlayer->position.x);
        return newPlayer;
    }
}

int screenSetUp() {
    initscr();
    noecho();
    refresh();
    srand(time(NULL));
    return 0;
}
///////////////////////// ROOMs SETUP ///////////////////////////////////
pRoom * mapSetUp() {
    pRoom * rooms;
    rooms = (pRoom *)malloc(sizeof(Room)*6);
    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);
    rooms[1] = createRoom(40, 2, 3, 20);
    drawRoom(rooms[1]);
    rooms[2] = createRoom(40, 10, 5, 7);
    drawRoom(rooms[2]);
    return rooms;
}

pRoom createRoom(int x, int y, int height, int width) {
    pRoom newRoom = (pRoom)malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    newRoom->door = (pPosition*)malloc(sizeof(Position) * 4);

    newRoom->door[0] = (pPosition)malloc(sizeof(Position));
    newRoom->door[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->door[0]->y = newRoom->position.y;

    newRoom->door[1] = (pPosition)malloc(sizeof(Position));
    newRoom->door[1]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->door[1]->y = newRoom->position.y + height;
    
    newRoom->door[2] = (pPosition)malloc(sizeof(Position));
    newRoom->door[2]->x = newRoom->position.x;
    newRoom->door[2]->y = rand() % (height - 2) + newRoom->position.y + 1;

    newRoom->door[3] = (pPosition)malloc(sizeof(Position));
    newRoom->door[3]->x = newRoom->position.x + width - 1;
    newRoom->door[3]->y = rand() % (height - 2) + newRoom->position.y + 1;
    return newRoom;
}

int drawRoom(pRoom room) {
    int x;
    int y;
    //draw top and bottom of the room
    for(x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height, x, "-");
    }
    //draw floors and side walls
    for(y = room->position.y + 1; y < room->position.y + room->height; y++) {
        //side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        //floor
        for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }
    //draw doors
    mvprintw(room->door[0]->y, room->door[0]->x, "#");
    mvprintw(room->door[1]->y, room->door[1]->x, "#");
    mvprintw(room->door[2]->y, room->door[2]->x, "#");
    mvprintw(room->door[3]->y, room->door[3]->x, "#");
}
////////////////////////// MOVEMENT ////////////////////////////////
int processInput(int ch, pPlayer user) {
    int newY;
    int newX;
    switch(ch) {
        /*move up*/
        case 'w':
        case 'W':
            newY = user->position.y - 1;
            newX = user->position.x;
            break;
        /*move down*/
        case 's':
        case 'S':
            newY = user->position.y + 1;
            newX = user->position.x;
            break;
        /*move left*/
        case 'a':
        case 'A':
            newY = user->position.y;
            newX = user->position.x - 1;
            break;
        /*move right*/
        case 'd':
        case 'D':
            newY = user->position.y;
            newX = user->position.x + 1;
            break;

        default:
            break;
    }
    checkPos(newY, newX, user);
}
int playerMove(int y, int x, pPlayer user) {
    mvprintw(user->position.y, user->position.x,  ".");

    user->position.y = y;
    user->position.x = x;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
    return 0;
}

int checkPos(int newY, int newX, pPlayer user) {
    int space;
    switch(mvinch(newY, newX)) {
        case '.':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}