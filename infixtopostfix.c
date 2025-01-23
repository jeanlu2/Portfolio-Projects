#include <stdio.h>
#include <string.h>

#define ARR_SIZE 20

typedef struct stack {
    char arr[ARR_SIZE];
    int top;
} stack;

void push(stack* stack, char c) {
    if (stack->top == ARR_SIZE-1) {
        printf("stack overflow!\n");
        return;
    }
    stack->top++;
    stack->arr[stack->top] = c;
}

void pop(stack* stack) {
    if (stack->top == -1) {
        printf("no elements in stack.\n");
        return;
    }
    stack->top--;
}

int peek(stack* stack) {
    return (stack->top == -1) ? 0 : stack->arr[stack->top];
}

int checkPreference(char op) {
    switch (op) {
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        default:
            return -1;
    }
}

void infixToPostfix(stack* stack, char* statement, char* ans) {
    int n = 0;
    for (int i = 0; i < strlen(statement); i++) {
        if (statement[i] == '1' || statement[i] == '2' || statement[i] == '3' || statement[i] == '4' || statement[i] == '5' || statement[i] == '6' || statement[i] == '7' || statement[i] == '8' || statement[i] == '9' || statement[i] == '0') {
            ans[n] = statement[i];
            n++;
        }
        else if (statement[i] == '+' || statement[i] == '-' || statement[i] == '*' || statement[i] == '/') {
            while (stack->top != -1 && checkPreference(statement[i]) <= checkPreference(stack->arr[stack->top])) {
                ans[n] = stack->arr[stack->top];
                n++;
                pop(stack);
            }
            push(stack, statement[i]);
         }      
    }

    while (stack->top != -1) {
        ans[n] = stack->arr[stack->top];
        n++;
        pop(stack);
    }

    ans[n] = '\0';
    
    printf("%s", ans);
}

int main()
{
    stack stack = {{0}, -1};
    char statement[ARR_SIZE] = {0};
    char ans[ARR_SIZE] = {0};
    fgets(statement, ARR_SIZE, stdin);
    infixToPostfix(&stack, statement, ans);
}