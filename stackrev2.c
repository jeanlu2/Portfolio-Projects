#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 20

typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct stack {
    node* arr[ARR_SIZE];
    int top;
} stack;

node* headNodeptr = NULL;

void pushFront(int val) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->val = val;
    newNode->next = headNodeptr;
    headNodeptr = newNode;
}

void printList() {
    node* ptr = headNodeptr;
    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

void sreverseList(stack* stack) {
    if (headNodeptr == NULL) {
        return;
    }
    node* ptr = headNodeptr;
    
    for (int i = 0; ptr != NULL; i++) {
        stack->arr[i] = ptr;
        ptr = ptr->next;
        stack->top++;
    }
    
    node* temp = stack->arr[stack->top];
    headNodeptr = temp;
    stack->top--;

    while (stack->top != -1) {
        temp->next = stack->arr[stack->top];
        stack->top--;
        temp = temp->next;
    }
    temp->next = NULL;
}

int main()
{
    stack stack;
    stack = (struct stack){{0}, -1};

    pushFront(1);
    pushFront(2);
    pushFront(3);
    pushFront(4);
    printList();
    sreverseList(&stack);
    printList();
    pushFront(5);
    printList();
}