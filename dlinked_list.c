#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node* prev;
	struct noe* next;
}node;

node* headNode_ptr = NULL;

node* createNode(int val) {
	node* newNode = malloc(sizeof(node));

	if (newNode == NULL) {
		return;
	}

	newNode->val = val;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

void pushFront(int val) {
	node* newNode = createNode(val);
	if (headNode_ptr == NULL) {
		headNode_ptr = newNode;
		return;
	}
	headNode_ptr->prev = newNode;
	newNode->next = headNode_ptr;
	headNode_ptr = newNode;
}

void pushBack(int val) {
	node* newNode = createNode(val);
	if (headNode_ptr == NULL) {
		headNode_ptr = newNode;
		return;
	}

	node* temp = headNode_ptr;
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = newNode;
	newNode->prev = temp;
}

void printList() {
	node* temp = headNode_ptr;
	while (temp != NULL) {
		printf("%i ", temp->val);
		temp = temp->next;
	}
	printf("\n");
}

void reversePrint() {
	node* temp = headNode_ptr;

	if (temp == NULL) {
		return;
	}

	while (temp->next != NULL) {
		temp = temp->next;
	}

	while (temp != NULL) {
		printf("%i ", temp->val);
		temp = temp->prev;
	}
	printf("\n");
}

int main()
{
	for (int i = 1; i <= 10; i++) {
		pushBack(i);
		printList();
	}
	reversePrint();
}