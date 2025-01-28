#include <stdio.h>
#include <stdlib.h>

//implementation of a queue using a singly-linked list

typedef struct node {
    int val;
    struct node* next;
} node;

node* headNodeptr = NULL; //front
node* rearNodeptr = NULL; //rear

void enQueue(int val) {
    node* newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Error creating node.\n");
        return;
    }

    newNode->val = val;
    newNode->next = NULL;

    if (headNodeptr == NULL && rearNodeptr == NULL)
    {
        headNodeptr = rearNodeptr = newNode;
    }
    rearNodeptr->next = newNode;
    rearNodeptr = newNode;
}

void deQueue() {
    if (headNodeptr == NULL) {
        printf("List is empty. Can't perform deQueue operation.\n");
        return;
    }

    node* temp = headNodeptr;
    if (temp->next == NULL) {
        headNodeptr = rearNodeptr = NULL;
        free(temp);
        return;
    }
    headNodeptr = temp->next;
    free(temp);
}

void printQueue() {
    node* ptr = headNodeptr;
    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

int main()
{
    enQueue(1);
    enQueue(2);
    enQueue(3);
    printQueue();
    deQueue();
    printQueue();
    deQueue();
    printQueue();
    deQueue();
    printQueue();
    deQueue();
}