#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 7
#define COLS 9
#define STARTING_ROW 3
#define STARTING_COL 4

static int ASCII_VAL = 65;

struct player {
    int x, y;
};

char snakeBoard[ROWS][COLS] = {{'|', '-', '-', '-', '-', '-', '-', '-', '|'},
                               {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                               {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                               {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                               {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                               {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                               {'|', '_', '_', '_', '_', '_', '_', '_', '|'}};

void printBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", snakeBoard[i][j]);
        }
        printf("\n");
    }
}

int drawPlayer(int x, int y) {
    if (x < ROWS-1 && x > 0 && y < COLS-1 && y > 0)
    {
        snakeBoard[x][y] = (char)ASCII_VAL;
        return 0;
    }
    else
        return 1;
}

void clearPlayer(int x, int y) {
    if (x < ROWS-1 && x > 0 && y < COLS-1 && y > 0)
    {
        snakeBoard[x][y] = ' ';
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

void generateObject(int times) {
    srand(time(0));
    int randx = rand() % ROWS-1;
    int randy = rand() % COLS-1;

    if (snakeBoard[randx][randy] == 'X' || snakeBoard[randx][randy] == '|' || snakeBoard[randx][randy] == '-' || snakeBoard[randx][randy] == '_') {
        return;
    }
    if (times % 2 == 0) {
        snakeBoard[randx][randy] = '$';
    }
    return;
}

void checkCurrentPos(int x, int y) {
    if (snakeBoard[x][y] == '$' && ASCII_VAL < 90) {
        ASCII_VAL++;
    }
}

void outOfBounds(struct player* s, char c) {
    switch (c) {
        case 'w':
            s->x++;
            break;
        case 'a':
            s->y++;
            break;
        case 's':
            s->x--;
            break;
        case 'd':
            s->y--;
            break;
    }
}

int main()
{
    struct player player;
    player = (struct player){STARTING_ROW, STARTING_COL};
    bool running = false;
    int times = 0;
    printBoard();

    printf("Game Demo\n");
    printf("Press ('w', 'a', 's', 'd') to move, 'q' to quit..");

    while (!running)
    {
        char key;
        if (_kbhit()) {
            key = _getch();
            if (key == 'q')
            {
                running = true;
                break;
            }

            int prevx = player.x;
            int prevy = player.y;

            clearPlayer(prevx, prevy); //clear last move

            generateObject(times);
            times++;

            fetchMove(&player, key);

            checkCurrentPos(player.x, player.y);
            
            if (drawPlayer(player.x, player.y) != 0) //if out of bounds, keep there
            {
                outOfBounds(&player, key);
                drawPlayer(player.x, player.y);
            }

            printBoard();

            if (ASCII_VAL == 'W') {
                printf("You won! Thanks for playing!\n");
                break;
            }
        }
    }
}