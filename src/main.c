#include "rogue.h"
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
    connectDoors(rooms[1]->door[2], rooms[0]->door[0]);
    connectDoors(rooms[0]->door[3], rooms[2]->door[1]);
    
    return rooms;
}




