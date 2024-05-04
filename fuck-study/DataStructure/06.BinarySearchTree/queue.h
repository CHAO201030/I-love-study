#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define QUEUE_CAPACITY 4
#define QUEUE_POP_FAILED -1
#define QUEUE_PEEK_FAILED -1

typedef int E;

typedef struct {
	E* elements;
	int front;
	int rear;
	int size;
	int capacity;
}Queue;

Queue* queue_create();

void queue_destory(Queue* q);

void queue_push(Queue* q, E val);

E queue_pop(Queue* q);

bool queue_empty(Queue* q);