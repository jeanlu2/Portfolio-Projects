#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* next;
} node;

node* head_node = NULL;

void insert(int value) {
    node* temp = (node*) malloc(sizeof(node));
    temp->val = value;
    temp->next = head_node;
    head_node = temp;
}

void reverse_list() {
    node* next;
    node* prev = NULL;
    node* temp1 = head_node;
    while (temp1 != NULL) {
        next = temp1->next;
        temp1->next = prev;
        prev = temp1;
        temp1 = next;
    }
    head_node = prev;
}

void display_list(char* message) {

    printf("%s", message);

    node* ptr = head_node;
    while (ptr != NULL) {
        printf("%i ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

void free_list() {
    node* ptr = head_node;
    while (ptr != NULL) {
        node* temp = ptr;
        free(temp);
        ptr = ptr->next;
    }
}

int main()
{
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    display_list("original list: ");
    reverse_list();
    display_list("reversed list: ");

}