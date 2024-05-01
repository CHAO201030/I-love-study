#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef	char E;

typedef struct node {
	E val;
	struct node* next;
}Node;

typedef struct list {
	Node* head;
	Node* tail;
	int size;
}List;

List* create_list();

void print_list(const List* list);

void destroy_list(List* list);

void add_before_head(List* list, E val);

void add_behind_tail(List* list, E val);

void add_node(List* list, int idx, E val);

void delete_node(List* list, E val);

Node* find_by_index(const List* list, int idx);

Node* search_for_value(const List* list, E val);