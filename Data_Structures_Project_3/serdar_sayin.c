#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct listNode{
	int dest;
	struct listNode *next;
};

struct list{
	struct listNode *header;
};

struct graph{
	int numberOfVertices;
	struct list* array;
};