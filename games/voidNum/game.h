#include "functions.h"

extern char (*firstBoard)[COLS];
extern bool running;
char answer[ARR_SIZE] = {0};

// Timer thread function
DWORD WINAPI TimerThread(LPVOID lpParam) {
    while (TIMELEFT > 0) {
        printf("\rTime remaining: %d seconds", TIMELEFT); // Print timer each 5 seconds
        fflush(stdout);
        Sleep(5000); // Sleep for 5 seconds
        TIMELEFT -= 5;
    }
    return 0;
}

void initializeGame() {
    // Initialize player, board...
    firstBoard = selectBoard();
    printBoard(firstBoard);
}

void showInstructions() {

    printf("--Welcome to voidNum--\n\n");
    
    printf("You have %i seconds to MOVE and MEMORIZE the numbers between %i boards\n", TIMESET, END);

    printf("Press ('w', 'a', 's', 'd') to move, 'q' to quit..\n\n");

    printf("If you're ready, press 'ENTER'...\n");
    
    while (1) 
    {
        if (_kbhit()) {
            char key = _getch();

            if (key == '\r' || key == '\n') {
                for (int i = 3; i != 0; i--) {
                    printf("%i\n", i);
                    Sleep(1000);
                }
                break;
                return;
            }
        }
    }
}

char playGameLoop() {
    struct player player = {STARTING_ROW, STARTING_COL};
    int i = 0;

    while (!running) {
            if (_kbhit()) {
                char key = _getch();
                    if (key == 'q') {
                         return 'L'; // Return a losing signal
                    }

                    int prevx = player.x;
                    int prevy = player.y;

                    clearPlayer(prevx, prevy, firstBoard); 
                    fetchMove(&player, key);

                     if (drawPlayer(player.x, player.y, firstBoard) != 0) {

                        if (outOfBounds(&player, key, firstBoard) == 1) { 

                            firstBoard = checkBoard(&player, firstBoard);  
                            answer[i++] = (char) calculateBoardValue(firstBoard) + '0';
                            locatePlayer(&player, firstBoard); 
                            TIMES++;
                        }
                        drawPlayer(player.x, player.y, firstBoard); 
                     }
                     printBoard(firstBoard);

                     if (TIMELEFT == 0) { 
                        printf("Got to be faster next time!\n");
                        return 'L';
                        }
                    }

                    if (TIMES == END) {
                        answer[i] = '\0';
                        char input[ARR_SIZE] = {0};
                        printf("Order of Numbers: ");
                        fgets(input, ARR_SIZE, stdin);
                        // Remove newline character from input string if present
                        size_t len = strlen(input);
                        
                        if (len > 0 && input[len-1] == '\n') {
                            input[len-1] = '\0';
                        }

                        if (strcmp(answer, input) == 0) {
                            return 'W'; // Winning signal
                        } else {
                            return 'L';
                        }
                    }
                }
                return 'L';
            }
