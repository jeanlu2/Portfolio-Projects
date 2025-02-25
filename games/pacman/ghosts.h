#include "movelist.h"
#include <stdbool.h>
#include <string.h>

#define MOVE_CURSOR_TO(x, y) printf("\033[%d;%dH", (x), (y))
#define CLEAR_POSITION(x, y) MOVE_CURSOR_TO((x), (y)); printf(" ")

#define BSTARTING_ROW 12
#define BSTARTING_COL 12

#define ISTARTING_ROW 14
#define ISTARTING_COL 12 //x

#define PSTARTING_ROW 13
#define PSTARTING_COL 11

#define CSTARTING_ROW 13
#define CSTARTING_COL 13

#define MOVEARR_B 21
#define SCATTERARR_B

#define SIDEROW_L 12
#define SIDECOL_L 0

#define SIDEROW_R 12
#define SIDECOL_R 25

#define LAST_MOVES 15 //?check
#define TCHASE_MODE 3

#define MOVEARR_P 9
#define MOVEARR_C 9

void hideCursor()
{
    printf("\033[?25l");
}

enum mode {chase, scatter};

enum mode BcurrentMode = chase;

enum mode PcurrentMode = chase;

enum mode IcurrentMode = chase;

enum mode CcurrentMode = chase;

struct ghost blinky = {BSTARTING_ROW, BSTARTING_COL, false};

//coordinates from box, to player spawn
struct player moveArrB[MOVEARR_B] = {{11, 12}, {10, 12}, {9, 12}, {9, 13}, {9, 14}, {9, 15}, {9, 16}, {10, 16}, {11, 16}, {12, 16}, {13, 16}, {14, 16}, {15, 16}, {16, 16}, {17, 16}, {18, 16}, {19, 16}, {20, 16}, {20, 15}, {20, 14}, {20, 13}};

void directBlinky(struct player (*arr)[], struct ghost* blinky) //apply the stated above
{
    for (int i = 0; i < MOVEARR_B; i++)
        enQueueB((*arr)[i], blinky);

    return;
}

struct player moveArrP[MOVEARR_P] = {{12, 11}, {11, 11}, {11, 12}, {10, 12}, {9, 12}, {9, 11}, {9, 10}, {9, 9}, {9, 8}};
struct player moveArrC[MOVEARR_C] = {{12, 13}, {11, 13}, {11, 12}, {10, 12}, {9, 12}, {9, 13}, {9, 14}, {9, 15}, {9, 16}};

struct ghost pinky = {PSTARTING_ROW, PSTARTING_COL, false, false};
struct ghost clyde = {CSTARTING_ROW, CSTARTING_COL, false, false};

void directPinky(struct ghost* pinky) 
{
    for (int i = 0; i < MOVEARR_P; i++)
        enQueueP(moveArrP[i], pinky);

    return;
}

void directClyde(struct ghost* clyde) 
{
    for (int i = 0; i < MOVEARR_C; i++)
        enQueueC(moveArrC[i], clyde);

    return;
}

#define DEPROW_C 9
#define DEPCOL_C 16

#define DEPROW_P 9
#define DEPCOL_P 8

int top = -1;
int rear = -1;

struct player lastMoves[LAST_MOVES];

void resetLastMoves() {
    memset(lastMoves, -1, sizeof(lastMoves));
}
void storeLastGhostMoves(struct player* blinky)
{
    if (rear == LAST_MOVES)
    {
        rear = top = -1;
        return;
    }
    else if (top == -1 && rear == -1)
    {
        resetLastMoves();
        lastMoves[0].x = blinky->x;
        lastMoves[0].y = blinky->y;
        top = rear = 0;
        return;
    }
    rear++;
    lastMoves[rear].x = blinky->x;
    lastMoves[rear].y = blinky->y;
}

int handleSidePath(struct player* player, struct ghost* blinky)
{
    if ((blinky->x == SIDEROW_L) && (blinky->y == SIDECOL_L))
    {
        pacBoard[blinky->x][blinky->y] = empty;
        CLEAR_POSITION(blinky->x +1, blinky->y + 1);
        blinky->x = SIDEROW_R; blinky->y = SIDECOL_R;
        return 1;
    }
    if ((player->x == SIDEROW_L) && (player->y == SIDECOL_L))
    {
        pacBoard[player->x][player->y] = empty;
        CLEAR_POSITION(player->x +1, player->y + 1);
        player->x = SIDEROW_R; player->y = SIDECOL_R;
        return 1;
    }
    if ((blinky->x == SIDEROW_R) && (blinky->y == SIDECOL_R))
    {
        pacBoard[blinky->x][blinky->y] = empty;
        CLEAR_POSITION(blinky->x +1, blinky->y + 1);
        blinky->x = SIDEROW_L; blinky->y = SIDECOL_L;
        return 1;
    }
    if ((player->x == SIDEROW_R) && (player->y == SIDECOL_R))
    {
        pacBoard[player->x][player->y] = empty;
        CLEAR_POSITION(player->x +1, player->y + 1);
        player->x = SIDEROW_L; player->y = SIDECOL_L;
        return 1;
    }
    return 0;
}