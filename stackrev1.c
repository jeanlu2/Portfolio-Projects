#include <stdio.h>

#define ARR_SIZE 20

typedef struct stack {
    char arr[ARR_SIZE];
    int top;
}stack;

void reverseString(char arr[], stack* stack) {
    for (int i = 0; i < ARR_SIZE; i++) {
        stack->arr[i] = arr[i];
        stack->top++;
    }

    for (int j = 0;stack->top != -1; j++) {
        arr[j] = stack->arr[stack->top];
        stack->top--;
    }
}

int main()
{
    char arr[ARR_SIZE] = {0};
    stack stack;
    stack = (struct stack){{0}, -1};

    printf("enter a string (0-20): ");
    scanf("%s", arr);

    reverseString(arr, &stack);

    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%c", arr[i]);
    }
        
}