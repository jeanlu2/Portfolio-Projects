#include <stdio.h>
#include <stdbool.h>

/*int add(int a, int b)
{
    return a+b;
}*/

bool ex(int i) {
    return (i % 2 == 0) ? true : false;
}

void print_if(int arr[], bool (*fptr)(int), int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        if (!fptr(arr[i])) {
            printf("%i ", arr[i]);
        }
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 123, 432, 54};
    int size = sizeof(arr) / sizeof(arr[0]);

    print_if(arr, ex, size);

    //int (*fptr)(int, int) = add;
    //printf("%i", fptr(10, 9));
}

