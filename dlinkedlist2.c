#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int val;
    struct node* next;
    struct node* prev;
} node;

node* headNodeptr = NULL;

node* createNode(int val) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->val = val;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void pushFront(int val) {
    node* newNode = createNode(val);
    if (headNodeptr == NULL) {
        headNodeptr = newNode;
        return;
    }
    newNode->next = headNodeptr;
    headNodeptr->prev  = newNode;
    headNodeptr = newNode;
}

void pushBack(int val) {
    node* newNode = createNode(val);
    if (headNodeptr == NULL) {
        headNodeptr = newNode;
        return;
    }
    node* ptr = headNodeptr;
    while (ptr->next != NULL) {
        ptr = ptr->next; //go to the last node in list
    }
    ptr->next = newNode;
    newNode->prev = ptr;

}

void printList() {
    node* ptr = headNodeptr;
    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

void reversePrint() {
    node* ptr = headNodeptr;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->prev;
    }
    printf("\n");
}

void searchElement(int val) {
    node* ptr = headNodeptr;

    bool found = false;

    for (int i = 1; ptr != NULL; i++) {
        if (ptr->val == val) {
            found = true;
            printf("val found in index: %i\n", i);
            break;
        }
        ptr = ptr->next;
    }
    if (found == false) {
        printf("value not in list\n");
    }
}

void freeList() {
    node* ptr = headNodeptr;
    while (ptr != NULL) {
        node* temp_next = ptr->next;
        free(ptr);
        ptr = temp_next; 
    }
}

int main()
{
    pushBack(1);
    pushBack(2);
    pushBack(3);
    pushBack(4);
    pushFront(0);
    printList();
    searchElement(4);
    reversePrint();
    freeList();
}