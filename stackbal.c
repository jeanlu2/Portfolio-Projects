#include <stdio.h>
#include <stdbool.h>

#define ARR_SIZE 20

typedef struct stack {
    char arr[ARR_SIZE];
    int top;
} stack;

bool checkParentheses(char *s, stack* stack);

int main()
{
    char statement[ARR_SIZE];
    stack stack = {{0}, -1};
    fgets(statement, ARR_SIZE, stdin);

    if (checkParentheses(statement, &stack)) {
         printf("parentheses balanced.\n");
    } 
    else {
        printf("parentheses not balanced.\n");
    }
}

bool checkParentheses(char *arr, stack* stack) {
    for (int i = 0; i < ARR_SIZE; i++) {
        if (arr[i] == '(' || arr[i] == '{' || arr[i] == '[') {
            stack->top++;
            stack->arr[stack->top] = arr[i];
        }
        else if (arr[i] == ')' || arr[i] == '}' || arr[i] == ']') {
            if (stack->top == -1) {
                return false;
            }
            else if (stack->arr[stack->top] == '(' && arr[i] == ')' || stack->arr[stack->top] == '[' && arr[i] == ']' || stack->arr[stack->top] == '{' && arr[i] == '}') {
                stack->top--;
            }
        }
    }
    return (stack->top == -1) ? true : false;
}