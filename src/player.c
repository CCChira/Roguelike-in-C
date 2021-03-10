#include "rogue.h"
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
        case '#':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}