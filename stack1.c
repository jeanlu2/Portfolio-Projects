#include <stdio.h>

#define ARR_SIZE 10

typedef struct stack {
    int arr[ARR_SIZE];
    int top;
} stack;

void push(stack* stack, int num) {
    
    if (stack->top < ARR_SIZE) {
        stack->top++;
        stack->arr[stack->top] = num;
        return;
    }
    printf("max size reached\n");
}

int top(stack* stack) {
    return stack->arr[stack->top];
}

void pop(stack* stack) {
    if (stack->top == -1) {
        printf("no element to pop\n");
        return;
    }
    stack->top--;
}

void printStack(stack* stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%i ", stack->arr[i]);
    }
    printf("\n");
}       

int main()
{
    stack stack;
    stack = (struct stack){{0}, -1};

   for (int i = 0; i < 4; i++) {
        push(&stack, i);
        printStack(&stack);
    }
    
    pop(&stack);
    printStack(&stack);
}