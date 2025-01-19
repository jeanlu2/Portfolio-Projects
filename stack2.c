#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* next;
} node;

node* headNodeptr = NULL;

void push(int val) {
    node* newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL) {
        return;
    }
    newNode->val = val;
    newNode->next = headNodeptr;
    headNodeptr = newNode;
}

void pop() {
    if (headNodeptr == NULL) {
        return;
    }
    node* ptr = headNodeptr;
    headNodeptr = ptr->next;
    free(ptr);
}

void printStack() {
    node* ptr = headNodeptr;
    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

int main()
{
    push(1);
    push(2);
    push(3);
    push(4);
    printStack();
    pop();
    printStack();
    int x = 2;
    x==2;
}