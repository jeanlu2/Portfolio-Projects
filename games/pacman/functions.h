#include "ghosts.h"

#define FROW 15
#define FCOL 12

bool TIMEFLAG = false;
bool CASHFLAG = false;

unsigned int UP;
unsigned int DOWN;
unsigned int LEFT;
unsigned int RIGHT;

unsigned int PLAYERANL = 0;
unsigned int PLAYERANR = 0;
unsigned int PLAYERANU = 0;
unsigned int PLAYERAND = 0;

void clearConsole() {
    printf("\033[H\033[J");  // ANSI escape code to clear the screen
}

void initializeAnimation(struct ghost* blinky, struct ghost* pinky, struct ghost* clyde)
{
    blinky->animation = pinky->animation = clyde->animation = 0;
}

void frightenGhosts(struct ghost* blinky, struct ghost* pinky, struct ghost* clyde)
{
    blinky->isFrightened = pinky->isFrightened = clyde->isFrightened = true;
}

bool areFrightened(struct ghost* blinky, struct ghost* pinky, struct ghost* clyde)
{
    if (blinky->isFrightened || pinky->isFrightened || clyde->isFrightened)
    {
        return true;
    }
    return false;
}

void checkPlayerPos(struct player* player, struct ghost* blinky, struct ghost* pinky, struct ghost* clyde)
{
    if (CASHFLAG)
    {
        if (player->x == FROW && player->y == FCOL)
        {
            frightenGhosts(blinky, pinky, clyde);
            CASHFLAG = false;
        }
    }
    return;
}

void checkGhostsPos(struct player* player, struct ghost* blinky, struct ghost* pinky, struct ghost* clyde)
{
    if (player->x == blinky->x && player->y == blinky->y && blinky->isFrightened)
    {
        Sleep(500); //visual queue
        blinky->x = BSTARTING_ROW; blinky->y = BSTARTING_COL;
        BfrontNodeptr = BrearNodeptr = NULL; //empty queue, restart
        directBlinky(&moveArrB, blinky);
        blinky->isFrightened = true;

        for (int i = 0; i < 10; i++)
        {
            struct player tempDelayB = {blinky->x, blinky->y}; 
            enQueueB(tempDelayB, blinky);
        }
        blinky->isFrightened = false;
    }
    else if (player->x == pinky->x && player->y == pinky->y && pinky->isFrightened)
    {
        Sleep(500);
        pinky->x = PSTARTING_ROW; pinky->y = PSTARTING_COL;
        PfrontNodeptr = PrearNodeptr = NULL;
        pinky->outOfBox = pinky->isOnWall = false;
        directPinky(pinky);
        pinky->isFrightened = true;

 
        for (int i = 0; i < 10; i++)
        {
            struct player tempDelayP = {pinky->x, pinky->y}; 
            enQueueP(tempDelayP, pinky);
        }
        pinky->isFrightened = false;
    }
    else if (player->x == clyde->x && player->y == clyde->y && clyde->isFrightened)
    {
        Sleep(500);
        clyde->x = CSTARTING_ROW; clyde->y = CSTARTING_COL;
        CfrontNodeptr = CrearNodeptr = NULL;
        clyde->outOfBox = clyde->isOnWall = false;
        directClyde(clyde);
        clyde->isFrightened = true;

        
        for (int i = 0; i < 10; i++)
        {
            struct player tempDelayC = {clyde->x, clyde->y}; 
            enQueueC(tempDelayC, clyde);
        }
        clyde->isFrightened = false;
    }
    return;
}

void InGameGameOver() {
    
    Sleep(1000);
    Sleep(1000);

    return;
}

void newPrintBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
                MOVE_CURSOR_TO(i + 1, j + 1);  // Move cursor to the row and column
                switch (pacBoard[i][j]) {
                    case empty:
                        printf(" ");
                        break;
                    case pellet:
                        printf(".");
                        break;
                    case wall:
                        printf("|");
                        break;
                    case sidewall:
                        printf("+");
                        break;
                    case ghost:
                        printf("#");
                        break;
                    case pacman:
                        printf("O");
                        break;
                    case vwalls:
                        printf("_");
                        break;
                    case vvwalls:
                        printf("-");
                        break;
                    case cash:
                        printf("$");
                        break;
                    case gameOver:
                        printf("X");
                        break;
                    default:
                        break;
            }
        }
        printf("\n");
    }
    fflush(stdout);  // Ensure that the output is printed immediately
}


int drawPlayer(int x, int y) {
    if (pacBoard[x][y] != wall && pacBoard[x][y] != sidewall && pacBoard[x][y] != vwalls && pacBoard[x][y] != vvwalls)
    {
        if (pacBoard[x][y] == pellet) {
            SCORE += 100; //handle score
        }
        pacBoard[x][y] = pacman;

        MOVE_CURSOR_TO(x+1, y+1);

        if (LEFT != 0)
        {
            if (PLAYERANL % 2 == 0)
            {
                printf("-");
                LEFT--;
                PLAYERANL++;
                return 0;
            }
            printf(">");
            LEFT--;
            PLAYERANL++;
            
        }
        else if (RIGHT != 0)
        {
            if (PLAYERANR % 2 == 0)
            {
                printf("-");
                RIGHT--;
                PLAYERANR++;
                return 0;
            }
            printf("<");
            RIGHT--;
            PLAYERANR++;
            
        }
        else if (UP != 0)
        {
            if (PLAYERANU % 2 == 0)
            {
                printf("-");
                UP--;
                PLAYERANU++;
                return 0;
            }
            printf("v");
            UP--;
            PLAYERANU++;
           
        }
        else if (DOWN != 0) {

            if (PLAYERAND % 2 == 0)
            {
                printf("-");
                DOWN--;
                PLAYERAND++;
                return 0;
            }
            printf("^");
            DOWN--;
            PLAYERAND++;
           
        }
        else {
            printf("v");
        }
        return 0;
    }
    else
        return 1;
}

void drawGhost(struct ghost* g, struct ghost* blinky, struct ghost* pinky, struct ghost* clyde) {
    if (pacBoard[g->x][g->y] != wall && pacBoard[g->x][g->y] != sidewall && pacBoard[g->x][g->y] != vwalls && pacBoard[g->x][g->y] != vvwalls) {
        if (pacBoard[g->x][g->y] == pellet) {
            g->wasOnPellet = true; // Track that the ghost was on a pellet
        } else {
            g->wasOnPellet = false;
        }
        pacBoard[g->x][g->y] = ghost;

        MOVE_CURSOR_TO(g->x+1, g->y+1);

        if (((blinky->animation % 2) == 0) && blinky->isFrightened) {
            printf("%%");
            
        } else if (((pinky->animation % 2) == 0) && pinky->isFrightened) {
            printf("%%");
           
        } else if (((clyde->animation % 2) == 0) && clyde->isFrightened) {
            printf("%%");
            
        } else {
            printf("#");
        }
        blinky->animation++;
        clyde->animation++;
        pinky->animation++;
    }
}

void clearPlayer(int x, int y) {
    if (pacBoard[x][y] != wall && pacBoard[x][y] != sidewall && pacBoard[x][y] != vwalls && pacBoard[x][y] != vvwalls)
    {
        pacBoard[x][y] = empty;
        CLEAR_POSITION(x + 1, y + 1); /////
    }
    else
        return;
}

void clearGhost(struct ghost* g) {
    if (pacBoard[g->x][g->y] != wall && pacBoard[g->x][g->y] != sidewall && pacBoard[g->x][g->y] != vwalls && pacBoard[g->x][g->y] != vvwalls) {
        if (g->wasOnPellet) {
            pacBoard[g->x][g->y] = pellet; // Restore the pellet if the ghost was on it
            MOVE_CURSOR_TO(g->x+1, g->y+1); 
            printf("."); //restore pellet
            g->wasOnPellet = false;
        } else {
            pacBoard[g->x][g->y] = empty;
            CLEAR_POSITION(g->x + 1, g->y + 1);
        }
    }
}

int moveBlinky(struct player* player, struct ghost* blinky) {
    if ((blinky->x == player->x) && (blinky->y == player->y)) return 1; // game over! check in all directions
    else if ((blinky->x == player->x-1) && (blinky->y == player->y)) return 1;
    else if ((blinky->x == player->x+1) && (blinky->y == player->y)) return 1;
    else if ((blinky->x == player->x) && (blinky->y-1 == player->y)) return 1;
    else if ((blinky->x == player->x) && (blinky->y+1 == player->y)) return 1;

    blinky->x = BfrontNodeptr->playerpos.x;
    blinky->y = BfrontNodeptr->playerpos.y;

    deQueueB();
    return 0;
}

int moveClyde(struct player* player, struct ghost* clyde) {
    if ((clyde->x == player->x) && (clyde->y == player->y)) return 1; // game over! check in all directions
    else if ((clyde->x == player->x-1) && (clyde->y == player->y)) return 1;
    else if ((clyde->x == player->x+1) && (clyde->y == player->y)) return 1;
    else if ((clyde->x == player->x) && (clyde->y-1 == player->y)) return 1;
    else if ((clyde->x == player->x) && (clyde->y+1 == player->y)) return 1;

    if (((clyde->x != DEPROW_C) || (clyde->y != DEPCOL_C)) && (clyde->outOfBox == false))
    {
        clyde->x = CfrontNodeptr->playerpos.x;
        clyde->y = CfrontNodeptr->playerpos.y;

        deQueueC();
        return 0;
    } 

    else if (clyde->isOnWall == false)
    {
        clyde->outOfBox = true;

        if ((pacBoard[clyde->x+1][clyde->y] != vvwalls))
        {
            clyde->x++;
            return 0;
        }
        else {
            clyde->isOnWall = true;
        }
    }
    else
    {
        if ((pacBoard[clyde->x-1][clyde->y] != sidewall))
        {
            clyde->x--;
            return 0;
        }
        else {
            clyde->isOnWall = false;
        }
    }
    return 0;
}

int movePinky(struct player* player, struct ghost* pinky) {
    if ((pinky->x == player->x) && (pinky->y == player->y)) return 1; // game over! check in all directions
    else if ((pinky->x == player->x-1) && (pinky->y == player->y)) return 1;
    else if ((pinky->x == player->x+1) && (pinky->y == player->y)) return 1;
    else if ((pinky->x == player->x) && (pinky->y-1 == player->y)) return 1;
    else if ((pinky->x == player->x) && (pinky->y+1 == player->y)) return 1;

    if (((pinky->x != DEPROW_P) || (pinky->y != DEPCOL_P)) && (pinky->outOfBox == false))
    {
        pinky->x = PfrontNodeptr->playerpos.x;
        pinky->y = PfrontNodeptr->playerpos.y;

        deQueueP();
        return 0;
    } 

    else if (pinky->isOnWall == false)
    {
        pinky->outOfBox = true;

        if ((pacBoard[pinky->x-1][pinky->y] != sidewall))
        {
            pinky->x--;
            return 0;
        }
        else {
            pinky->isOnWall = true;
        }
    }
    else
    {
        if ((pacBoard[pinky->x+1][pinky->y] != vvwalls))
        {
            pinky->x++;
            return 0;
        }
        else {
            pinky->isOnWall = false;
        }
    }
    return 0;
}

void fetchMove(struct player* s, char c) {
    switch (c) {
        case 'w':
            s->x--;
            UP++;
            break;
        case 'a':
            s->y--;
            LEFT++;
            break;
        case 's':
            s->x++;
            DOWN++;
            break;
        case 'd':
            s->y++;
            RIGHT++;
            break;
        default:
            break;
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