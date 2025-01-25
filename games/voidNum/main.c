#include "game.h"

char (*firstBoard)[COLS];
bool running = false;
extern char answer[ARR_SIZE];

int main() {

    // Show instructions
    showInstructions();

    // Start the timer thread
    HANDLE hThread = CreateThread(NULL, 0, TimerThread, NULL, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create timer thread.\n");
        return 1;
    }

    // Initialize game
    initializeGame();

    // Play game loop
    char result = playGameLoop();

    WaitForSingleObject(hThread, INFINITE);

    if (result == 'W') {
        printf("YOU WIN! Thanks for playing!\n");
    } else {
        printf("YOU LOSE! Thanks for playing!\n");
    }
    printf("Answer was: %s\n", answer);

    // Close thread handle
    CloseHandle(hThread);
    
    return 0;
    
}    
    