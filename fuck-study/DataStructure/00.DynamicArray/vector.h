#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_CAPACITY 10

typedef int E;

typedef struct vector {
	E* elements;
	int size;
	int capacity;
}Vector;

Vector* vector_create();

void vector_destory(Vector* v);

void print_vector(const Vector* v);

void push_back(Vector* v, E data);

void push_front(Vector* v, E data);

E pop_back(Vector* v);

E pop_front(Vector* v);
