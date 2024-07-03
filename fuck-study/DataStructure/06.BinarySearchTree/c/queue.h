#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"BST.h"

#define MAX_CAPACITY 10

typedef TreeNode* E;

typedef struct queue {
	E* elements;
	int front;
	int rear;
	int size;
	int capacity;
}Queue;

Queue* queue_create();

void queue_destroy(Queue* q);

void queue_push(Queue* q, E val);

E queue_pop(Queue* q);

E queue_peek(Queue* q);

bool queue_empty(Queue* q);