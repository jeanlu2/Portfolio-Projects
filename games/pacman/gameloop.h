#include "functions.h"

#define SCARED_TIME 7.0
#define BLINKY_SPEED 5.0

void GameOver(struct player* player, struct ghost* blinky, struct ghost* pinky, struct ghost* clyde, int* running);
void Winner(struct player* player, struct ghost* blinky, struct ghost* pinky, struct ghost* clyde, int* running);

// Function to move the cursor to a specific line and column (row, col)
void moveCursorTo(int row, int col) {
    printf("\033[%d;%dH", row, col);  // ANSI escape code to move cursor
}

// Function to clear the line (so we can update it with new info)
void clearLine() {
    printf("\033[K");  // Clears the line from the cursor to the end
}

// Function to reset the cursor to the top-left of the console
void resetCursor() {
    printf("\033[H");  // Moves the cursor back to the top-left of the console
}

// Function to print the score at a fixed position (line 27)
void printScore(int score) {
    
    moveCursorTo(29, 1);  // Move the cursor to line 27, column 1
    clearLine();           // Clear the line (remove old score)
    printf("Score: %d", score);  // Print the updated score
    fflush(stdout);        // Make sure output is immediately visible
}

// Function to print the lives at a fixed position (line 28)
void printLives(int lives) {
    
    moveCursorTo(30, 1);  // Move the cursor to line 28, column 1
    clearLine();           // Clear the line (remove old lives count)
    printf("LIVES REMAINING: %i", lives);  // Print the updated lives count
    fflush(stdout);        // Make sure output is immediately visible
}


void startGame() {
    struct player player = {STARTING_ROW, STARTING_COL};
    int running = 0;
    int animation = 0;

    LIVES = 3;
    SCORE = 0;

    BfrontNodeptr = BrearNodeptr = NULL; // empty queue, restart
    PfrontNodeptr = PrearNodeptr = NULL;
    CfrontNodeptr = CrearNodeptr = NULL;

    pinky.outOfBox = pinky.isOnWall = false;
    clyde.outOfBox = clyde.isOnWall = false;
    blinky.isFrightened = pinky.isFrightened = clyde.isFrightened = false;

    blinky.x = BSTARTING_ROW; blinky.y = BSTARTING_COL;
    pinky.x = PSTARTING_ROW; pinky.y = PSTARTING_COL;
    clyde.x = CSTARTING_ROW; clyde.y = CSTARTING_COL;
    player.x = STARTING_ROW; player.y = STARTING_COL;


    initializeAnimation(&blinky, &pinky, &clyde);

    time_t start, end, start2, end2;
    double elapsed_time, elapsed_time2;

    clearConsole();
    newPrintBoard();
    printf("('w', 'a', 's', 'd') to move...\n");
    hideCursor();

    copyBoard();

    directBlinky(&moveArrB, &blinky);
    directPinky(&pinky);
    directClyde(&clyde);

    time(&start);

    while (!running) {

        char key;
        if (_kbhit()) {
            key = _getch();
        }

        if (pacBoard[FROW][FCOL] == cash && !CASHFLAG) {
            CASHFLAG = true;
        }

        checkPlayerPos(&player, &blinky, &pinky, &clyde);

        checkGhostsPos(&player, &blinky, &pinky, &clyde);

        time(&end);

        if (areFrightened(&blinky, &pinky, &clyde) && !TIMEFLAG) {
            time(&start2);
            TIMEFLAG = true;
        }

        elapsed_time = difftime(end, start);
        elapsed_time2 = difftime(end, start2);

        struct player prev = {blinky.x, blinky.y};

        if (elapsed_time2 >= SCARED_TIME) { // frightened for 5 seconds
            blinky.isFrightened = pinky.isFrightened = clyde.isFrightened = false;
            TIMEFLAG = false; // Reset TIMEFLAG after frightened state ends
            start2 = 0;
        }

        if (elapsed_time >= BLINKY_SPEED) { // slow down each n seconds
            enQueueB(prev, &blinky);
            time(&start);
        }
        enQueueB(player, &blinky); // enqueue player moves for each ghost

        int prevx = player.x;
        int prevy = player.y;

        int prevbx = blinky.x;
        int prevby = blinky.y;

        int prevpx = pinky.x;
        int prevpy = pinky.y;

        int prevcx = clyde.x;
        int prevcy = clyde.y;

        clearPlayer(prevx, prevy);
        clearGhost(&blinky);
        clearGhost(&pinky);
        clearGhost(&clyde);

        fetchMove(&player, key);

        if (moveBlinky(&player, &blinky) != 0 && !blinky.isFrightened) { // if blinky reaches player, LIVES-- (3 lives)
            InGameGameOver();

            BfrontNodeptr = BrearNodeptr = NULL; // empty queue, restart
            PfrontNodeptr = PrearNodeptr = NULL;
            CfrontNodeptr = CrearNodeptr = NULL;

            pinky.outOfBox = pinky.isOnWall = false;
            clyde.outOfBox = clyde.isOnWall = false;

            directBlinky(&moveArrB, &blinky);
            directPinky(&pinky);
            directClyde(&clyde);

            blinky.x = BSTARTING_ROW; blinky.y = BSTARTING_COL;
            pinky.x = PSTARTING_ROW; pinky.y = PSTARTING_COL;
            clyde.x = CSTARTING_ROW; clyde.y = CSTARTING_COL;
            player.x = STARTING_ROW; player.y = STARTING_COL;

            LIVES--;
            pacBoard[FROW][FCOL] = cash;
            newBoard[FROW][FCOL] = cash;
            MOVE_CURSOR_TO(FROW+1, FCOL+1);
            printf("$");

            GameOver(&player, &blinky, &pinky, &clyde, &running);
        }

        if (movePinky(&player, &pinky) != 0 && !pinky.isFrightened) { // if pinky reaches player, LIVES-- (3 lives)
            InGameGameOver();

            BfrontNodeptr = BrearNodeptr = NULL; // empty queue, restart
            PfrontNodeptr = PrearNodeptr = NULL;
            CfrontNodeptr = CrearNodeptr = NULL;

            pinky.outOfBox = pinky.isOnWall = false;
            clyde.outOfBox = clyde.isOnWall = false;

            directBlinky(&moveArrB, &blinky);
            directPinky(&pinky);
            directClyde(&clyde);

            blinky.x = BSTARTING_ROW; blinky.y = BSTARTING_COL;
            pinky.x = PSTARTING_ROW; pinky.y = PSTARTING_COL;
            clyde.x = CSTARTING_ROW; clyde.y = CSTARTING_COL;
            player.x = STARTING_ROW; player.y = STARTING_COL;

            LIVES--;
            pacBoard[FROW][FCOL] = cash;
            newBoard[FROW][FCOL] = cash;
            MOVE_CURSOR_TO(FROW+1, FCOL+1);
            printf("$");

            GameOver(&player, &blinky, &pinky, &clyde, &running);
        }

        if (moveClyde(&player, &clyde) != 0 && !clyde.isFrightened) { // if clyde reaches player, LIVES-- (3 lives)
            InGameGameOver();

            BfrontNodeptr = BrearNodeptr = NULL; // empty queue, restart
            PfrontNodeptr = PrearNodeptr = NULL;
            CfrontNodeptr = CrearNodeptr = NULL;

            pinky.outOfBox = pinky.isOnWall = false;
            clyde.outOfBox = clyde.isOnWall = false;

            directBlinky(&moveArrB, &blinky);
            directPinky(&pinky);
            directClyde(&clyde);

            blinky.x = BSTARTING_ROW; blinky.y = BSTARTING_COL;
            pinky.x = PSTARTING_ROW; pinky.y = PSTARTING_COL;
            clyde.x = CSTARTING_ROW; clyde.y = CSTARTING_COL;
            player.x = STARTING_ROW; player.y = STARTING_COL;

            LIVES--;
            pacBoard[FROW][FCOL] = cash;
            newBoard[FROW][FCOL] = cash;
            MOVE_CURSOR_TO(FROW+1, FCOL+1);
            printf("$");

            GameOver(&player, &blinky, &pinky, &clyde, &running);
        }

        if (drawPlayer(player.x, player.y) != 0) { // if out of bounds, keep there
            outOfBounds(&player, key);
            drawPlayer(player.x, player.y);
        }

        drawGhost(&blinky, &blinky, &pinky, &clyde);
        drawGhost(&pinky, &blinky, &pinky, &clyde);
        drawGhost(&clyde, &blinky, &pinky, &clyde);

        handleSidePath(&player, &blinky);
        handleSidePath(&player, &pinky);
        handleSidePath(&player, &clyde);

        printLives(LIVES);
        resetCursor();
        printScore(SCORE);
        resetCursor();

        Sleep(200);
    }
}

void restartGame() {
    cleanBoard();
    startGame();
}

void GameOver(struct player* player, struct ghost* blinky, struct ghost* pinky, struct ghost* clyde, int* running) {
    char c = 0;
    if ((LIVES == 0) || (SCORE == WINNING_SCORE)) {

        printLives(LIVES);
        resetCursor();
        
        Sleep(1000); //2 second delay when losing or winning
        clearConsole();

        if (SCORE == WINNING_SCORE) {printf("YOU WIN!\n"); }
        else {printf("YOU LOSE!\n");}

        printf("Thanks for playing!\n");
        printf("Want to play again? (y/n): ");
        printf("\nYOUR SCORE WAS: %i\n", SCORE);

        scanf(" %c", &c);
        if (c == 'y') {
            (*running) = 1;
            restartGame();
        } else {
            freeGhosts();
            printf("exiting the program...\n");
            for (int i = 5; i != 0; i--) {
                printf("%i\n", i);
                Sleep(500);
            }
            clearConsole();
            (*running) = 1;
            return;
        }
    }
}