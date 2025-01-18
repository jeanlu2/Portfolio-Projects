#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 9
#define STARTING_ROW 3
#define STARTING_COL 4

struct snake {
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

int drawSnake(int x, int y) {
    if (x < ROWS-1 && x > 0 && y < COLS-1 && y > 0)
    {
        snakeBoard[x][y] = 'X';
        return 0;
    }
    else
        printf("out-of-bounds, returning to starting position\n");
        return 1;
}

void clearSnake(int x, int y) {
    if (x < ROWS-1 && x > 0 && y < COLS-1 && y > 0)
    {
        snakeBoard[x][y] = ' ';
    }
    else
        return;
}


void fetchMove(struct snake* s, char c) {
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
int main()
{
    struct snake snake;
    snake = (struct snake){STARTING_ROW, STARTING_COL};
    bool running = false;
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

            int prevx = snake.x;
            int prevy = snake.y;

            clearSnake(prevx, prevy); //clean board

            fetchMove(&snake, key);
            
            if (drawSnake(snake.x, snake.y) != 0) //if out of bounds, return to starting position
            {
                snake.x = STARTING_ROW;
                snake.y = STARTING_COL;
            }

            printBoard();

        }
    }
}