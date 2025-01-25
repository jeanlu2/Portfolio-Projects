#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "boards.h"

struct player {
    int x, y;
};

void printBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

int drawPlayer(int x, int y, char board[ROWS][COLS]) {
    if (x < ROWS-1 && x > 0 && y < COLS-1 && y > 0)
    {
        board[x][y] = '@';
        return 0;
    }
    else
        return 1;
}

void clearPlayer(int x, int y, char board[ROWS][COLS]) {
    if (x < ROWS-1 && x > 0 && y < COLS-1 && y > 0)
    {
        board[x][y] = ' ';
    }
    else
        return;
}

void fetchMove(struct player* s, char c) {
    switch (c) {
        case 'w':
            s->x--;
            break;
        case 'a':
            s->y--;
            break;
        case 's':
            s->x++;
            break;
        case 'd':
            s->y++;
            break;
        default:
            printf("('w', 'a', 's', 'd') to move, 'q' to quit\n");
    }
}

int outOfBounds(struct player* s, char c, char board[ROWS][COLS]) {
    if (s->x == 3 && s->y == 17 && board[3][17] == ' ' || s->x == 3 && s->y == 0 && board[3][0] == ' ' || s->x == 0 && s->y == 8 && board[0][8] == ' ' || s->x == 6 && s->y == 8 && board[6][8] == ' ') {
        return 1;
    }
    switch (c) {
        case 'w':
            s->x++;
            return 0;
            break;
        case 'a':
            s->y++;
            return 0;
            break;
        case 's':
            s->x--;
            return 0;
            break;
        case 'd':
            s->y--;
            return 0;
            break;
    }
}

char (*selectBoard())[COLS] {
    srand(time(NULL));
    int val = rand() % 3;
    switch (val) {
        case 0:
            return gameBoardR;
        case 1:
            return gameBoardL;
        case 2:
            return gameBoardU;
        case 3:
            return gameBoardD;
    }
}

int calculateBoardValue(char board[ROWS][COLS]) {
    int boardVal;
    if (board == gameBoardRU) {
        boardVal = 1;
    }
    else if (board == gameBoardRD) {
        boardVal = 5;
    }
    else if (board == gameBoardRL) {
        boardVal = 3;
    }
    else if (board == gameBoardLU) {
        boardVal = 2;
    }
    else if (board == gameBoardLD) {
        boardVal = 4;
    }
    else if (board == gameBoardLR) {
        boardVal = 9;
    }
    else if (board == gameBoardDL) {
        boardVal = 6;
    }
    else if (board == gameBoardDR) {
        boardVal = 3;
    }
    else if (board == gameBoardDU) {
        boardVal = 8;
    }
    else if (board == gameBoardUL) {
        boardVal = 0;
    }
    else if (board == gameBoardUR) {
        boardVal = 7;
    }
    else if (board == gameBoardUD) {
        boardVal = 2;
    }
    return boardVal;
}

char (*checkBoard(struct player* player, char board[ROWS][COLS]))[COLS] {
    if (player->x == 3 && player->y == 17 && board[3][17] == ' ') {
        srand(time(NULL));
        int val = rand() % 2;
        switch (val) {
            case 0:
                return gameBoardLU;
            case 1:
                return gameBoardLD;
            case 2:
                return gameBoardLR;
        }
    }
    else if (player->x == 3 && player->y == 0 && board[3][0] == ' ') {
        srand(time(NULL));
        int val = rand() % 2;
        switch (val) {
            case 0:
                return gameBoardRU;
            case 1:
                return gameBoardRD;
            case 2:
                return gameBoardRL;
        }
    }
    else if (player->x == 0 && player->y == 8 && board[0][8] == ' ') {
        srand(time(NULL));
        int val = rand() % 2;
        switch (val) {
            case 0:
                return gameBoardDL;
            case 1:
                return gameBoardDR;
            case 2:
                return gameBoardDU;
        }
    }
    else if (player->x == 6 && player->y == 8 && board[6][8] == ' ') {
        srand(time(NULL));
        int val = rand() % 2;
        switch (val) {
            case 0:
                return gameBoardUL;
            case 1:
                return gameBoardUR;
            case 2:
                return gameBoardUD;
        }
    }
    else {
        return board;
    }
}

void locatePlayer(struct player* player, char board[ROWS][COLS]) {
    if (player->x == 3 && player->y == 17) {
        player->x = 3;
        player->y = 1;
    }
    else if (player->x == 3 && player->y == 0) {
        player->x = 3;
        player->y = 16;
    }
    else if (player->x == 0 && player->y == 8) {
        player->x = 5;
        player->y = 8;
    }
    else if (player->x == 6 && player->y == 8) {
        player->x = 1;
        player->y = 8;
    }
}