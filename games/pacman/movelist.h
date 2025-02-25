#include <stdlib.h>
#include "globals.h"

typedef struct Blinkynode {
    struct player playerpos;
    struct Blinkynode* next;
} Bnode;

typedef struct PinkyNode {
    struct player playerpos;
    struct PinkyNode* next;
} Pnode;

typedef struct Clydenode {
    struct player playerpos;
    struct Clydenode* next;
} Cnode;

typedef struct Inkynode {
    struct player playerpos;
    struct Inkynode* next;
} Inode;

Bnode* BfrontNodeptr = NULL;
Bnode* BrearNodeptr = NULL;

Pnode* PfrontNodeptr = NULL;
Pnode* PrearNodeptr = NULL;

Cnode* CfrontNodeptr = NULL;
Cnode* CrearNodeptr = NULL;

Inode* IfrontNodeptr = NULL;
Inode* IrearNodeptr = NULL;


//Blinky
Bnode* createNodeB(struct player playerpos)
{
    Bnode* newNode = (Bnode*) malloc(sizeof(Bnode));
    newNode->playerpos.x = playerpos.x;
    newNode->playerpos.y = playerpos.y;
    newNode->next = NULL;

    return newNode;
}

void enQueueB(struct player playerpos, struct ghost* blinky)
{
    Bnode* newNode = createNodeB(playerpos);
    if (BfrontNodeptr == NULL && BrearNodeptr == NULL)
    {
        BfrontNodeptr = BrearNodeptr = newNode;
        return;
    }
    else if (playerpos.x == BrearNodeptr->playerpos.x && playerpos.y == BrearNodeptr->playerpos.y && blinky->isFrightened == false) {
        return; //if repeated coordinate, return
    }
    BrearNodeptr->next = newNode;
    BrearNodeptr = newNode;
}

void deQueueB()
{
    if (BfrontNodeptr == BrearNodeptr)
    {
        return;
    }
    Bnode* temp = BfrontNodeptr;
    BfrontNodeptr = temp->next;
    free(temp);
}

//Pinky

Pnode* createNodeP(struct player playerpos)
{
    Pnode* newNode = (Pnode*) malloc(sizeof(Pnode));
    newNode->playerpos.x = playerpos.x;
    newNode->playerpos.y = playerpos.y;
    newNode->next = NULL;

    return newNode;
}

void enQueueP(struct player playerpos, struct ghost* pinky)
{
    Pnode* newNode = createNodeP(playerpos);
    if (PfrontNodeptr == NULL && PrearNodeptr == NULL)
    {
        PfrontNodeptr = PrearNodeptr = newNode;
        return;
    }
    else if (playerpos.x == PrearNodeptr->playerpos.x && playerpos.y == PrearNodeptr->playerpos.y && pinky->isFrightened == false) {
        return; //if repeated coordinate, return
    }
    PrearNodeptr->next = newNode;
    PrearNodeptr = newNode;
}

void deQueueP()
{
    if (PfrontNodeptr == PrearNodeptr)
    {
        return;
    }
    Pnode* temp = PfrontNodeptr;
    PfrontNodeptr = temp->next;
    if (!temp) {
        free(temp);
    }
}

//Clyde

Cnode* createNodeC(struct player playerpos)
{
    Cnode* newNode = (Cnode*) malloc(sizeof(Cnode));
    newNode->playerpos.x = playerpos.x;
    newNode->playerpos.y = playerpos.y;
    newNode->next = NULL;

    return newNode;
}

void enQueueC(struct player playerpos, struct ghost* clyde)
{
    Cnode* newNode = createNodeC(playerpos);
    if (CfrontNodeptr == NULL && CrearNodeptr == NULL)
    {
        CfrontNodeptr = CrearNodeptr = newNode;
        return;
    }
    else if (playerpos.x == CrearNodeptr->playerpos.x && playerpos.y == CrearNodeptr->playerpos.y && clyde->isFrightened == false) {
        return; //if repeated coordinate, return
    }
    CrearNodeptr->next = newNode;
    CrearNodeptr = newNode;
}

void deQueueC()
{
    if (CfrontNodeptr == CrearNodeptr)
    {
        return;
    }
    Cnode* temp = CfrontNodeptr;
    CfrontNodeptr = temp->next;
    free(temp);
}

//Inky

Inode* createNodeI(struct player playerpos)
{
    Inode* newNode = (Inode*) malloc(sizeof(Inode));
    newNode->playerpos.x = playerpos.x;
    newNode->playerpos.y = playerpos.y;
    newNode->next = NULL;

    return newNode;
}

void enQueueI(struct player playerpos)
{
    Inode* newNode = createNodeI(playerpos);
    if (IfrontNodeptr == NULL && IrearNodeptr == NULL)
    {
        IfrontNodeptr = IrearNodeptr = newNode;
        return;
    }
    else if (playerpos.x == IrearNodeptr->playerpos.x && playerpos.y == IrearNodeptr->playerpos.y) {
        return; //if repeated coordinate, return
    }
    IrearNodeptr->next = newNode;
    IrearNodeptr = newNode;
}

void deQueueI()
{
    if (IfrontNodeptr == IrearNodeptr)
    {
        return;
    }
    Inode* temp = IfrontNodeptr;
    IfrontNodeptr = temp->next;
    free(temp);
}

void freeGhosts()
{
    Bnode* ptr = BfrontNodeptr;
    while (ptr != NULL) {
        Bnode* next = ptr->next;
        free(ptr);
        ptr = next;
    }
    BfrontNodeptr = BrearNodeptr = NULL;
    
    Cnode* ptrC = CfrontNodeptr;
    while (ptrC != NULL) {
        Cnode* next = ptrC->next;
        free(ptrC);
        ptrC = next;
    }
    CfrontNodeptr = CrearNodeptr = NULL;

    Inode* ptrI = IfrontNodeptr;
    while (ptrI != NULL) {
        Inode* next = ptrI->next;
        free(ptrI);
        ptrI = next;
    }
    IfrontNodeptr = IrearNodeptr = NULL;

    Pnode* ptrP = PfrontNodeptr;
    while (ptrP != NULL) {
        Pnode* next = ptrP->next;
        free(ptrP);
        ptrP = next;
    }
    PfrontNodeptr = PrearNodeptr = NULL;
}