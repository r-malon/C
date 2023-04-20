#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

int
main()
{
	int number = 123456;
	char *word = "Hello World!";
	Node *head = malloc(sizeof(Node));
	Node *left_node = malloc(sizeof(Node));
	head->data = &number;
	head->left = left_node;
	head->left->data = &word;

	printf("%p\n", (head->data));
	printf("%s\n", *(char *)(head->left->data));
	printf("%d\n", *(int *)(head->data));

	return 0;
}
