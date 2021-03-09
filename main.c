#include <ncurses.h>
#include <stdlib.h>

struct Player {
    int xPos;
    int yPos;
    int health;
};
typedef struct Player Player;
typedef struct Player* pPlayer;

int screenSetUp();
int mapSetUp();
int processInput(int ch, pPlayer user);
int playerMove(int y, int x, pPlayer user);
pPlayer playerSetUp();

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
        newPlayer->xPos = 14;
        newPlayer->yPos = 14;
        newPlayer->health = 20;
        mvprintw(newPlayer->yPos, newPlayer->xPos, "@");
        move(newPlayer->yPos, newPlayer->xPos);
        return newPlayer;
    }
}

int screenSetUp() {
    initscr();
    noecho();
    refresh();
    return 0;
}

int mapSetUp() {
    mvprintw(13, 13, "........");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "........");
    return 0;
}

int processInput(int ch, pPlayer user) {
    switch(ch) {
        /*move up*/
        case 'w':
        case 'W':
            playerMove(user->yPos - 1, user->xPos, user);
            break;
        /*move down*/
        case 's':
        case 'S':
            playerMove(user->yPos + 1, user->xPos, user);
            break;
        /*move left*/
        case 'a':
        case 'A':
            playerMove(user->yPos, user->xPos - 1, user);
            break;
        /*move right*/
        case 'd':
        case 'D':
            playerMove(user->yPos , user->xPos + 1, user);
            break;

        default:
            break;
    }
}
int playerMove(int y, int x, pPlayer user) {
    mvprintw(user->yPos, user->xPos,  ".");

    user->yPos = y;
    user->xPos = x;

    mvprintw(user->yPos, user->xPos, "@");
    return 0;
}