#include "rogue.h"
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

    newRoom->door[2] = (pPosition)malloc(sizeof(Position));
    newRoom->door[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->door[2]->y = newRoom->position.y + height;
    
    newRoom->door[1] = (pPosition)malloc(sizeof(Position));
    newRoom->door[1]->x = newRoom->position.x;
    newRoom->door[1]->y = rand() % (height - 2) + newRoom->position.y + 1;

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
int connectDoors(pPosition door1, pPosition door2) {

    Position temp;
    Position previous;
    temp.x = door1->x;
    temp.y = door1->y;
    int count = 0;
    while(1) {
        //build left
        if(abs((temp.x - 1) - door2->x) < abs(temp.x - door2->x) && (mvinch(temp.y, temp.x - 1) == ' ') ) {
            previous.x = temp.x;
            temp.x = temp.x - 1;   
        //build right
        } else if(abs((temp.x + 1) - door2->x) < abs(temp.x - door2->x) && (mvinch(temp.y, temp.x + 1) == ' ') ) {
            previous.x = temp.x;
            temp.x = temp.x + 1;   
        //build down
        }  else if(abs((temp.y + 1) - door2->y) < abs(temp.y - door2->y) && (mvinch(temp.y + 1, temp.x) == ' ') ) {
            previous.y = temp.y;
            temp.y = temp.y + 1;
        } else if(abs((temp.y - 1) - door2->y) < abs(temp.y - door2->y) && (mvinch(temp.y - 1, temp.x) == ' ') ) {
            previous.y = temp.y;
               temp.y = temp.y - 1;
        } else {
            if(count == 0) {
                temp = previous;
                count++;
                continue;
            }
            else{
                return 0;
            }
            
        }
        mvprintw(temp.y, temp.x, "#");
    }
    return 1;
}