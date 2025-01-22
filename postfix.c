#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 20

typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct stack {
    node* headNodeptr;
    node* top;
} stack;

void push(stack* stack, int val) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->val = val;
    newNode->next = stack->headNodeptr;
    stack->headNodeptr = newNode;
    stack->top = newNode;
}

void pop(stack* stack) {
    if (stack->headNodeptr == NULL) {
        return;
    }
    node* temp = stack->headNodeptr;
    stack->top = temp->next;
    stack->headNodeptr = temp->next;
    free(temp);
}

void printStack(stack* stack) {
    node* ptr = stack->headNodeptr;
    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

int evaluate(char c, char op1, char op2) {
    switch (c) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
    }
}

int evaluatePostfix(stack* stack, char* statement) {
    for (int i = 0; i < strlen(statement); i++) {
        if (statement[i] == '1' || statement[i] == '2' || statement[i] == '3' || statement[i] == '4' || statement[i] == '5' || statement[i] == '6' || statement[i] == '7' || statement[i] == '8' || statement[i] == '9') {
            push(stack, statement[i] - 48);
        }
        else if (statement[i] == '+' || statement[i] == '-' || statement[i] == '*' || statement[i] == '/') {
            char op1 = stack->top->val;
            pop(stack);
            char op2 = stack->top->val;
            pop(stack);
            int result = evaluate(statement[i], op1, op2);
            push(stack, result);
        }
    }
    return (stack->top == NULL) ? 0 : stack->top->val;
}

int main()
{
    stack stack = {NULL, NULL};

    char input[ARR_SIZE];
    fgets(input, ARR_SIZE, stdin);

    if (evaluatePostfix(&stack, input) != 0) {
        printf("%i", evaluatePostfix(&stack, input));
    }
    else {
        printf("input not valid.\n");
    }
}