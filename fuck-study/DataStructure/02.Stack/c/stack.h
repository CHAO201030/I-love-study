#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define STACK_POP_FAILED -1
#define STACK_PEEK_FAILED -1

typedef int E;

typedef struct node {
	E val;
	struct node* next;
}Node;

typedef struct stack {
	Node* top;
	int size;
}Stack;

Stack* stack_create(void);

void stack_destory(Stack* s);

void stack_push(Stack* s, E val);

E stack_pop(Stack* s);

E stack_peek(Stack* s);

bool stack_empty(Stack* s);