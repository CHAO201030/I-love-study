#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 12

typedef struct node {
	int data;
	struct node* next;
}Node;

typedef struct hashmap {
	Node* table[MAX_SIZE];
	int size;
}HashMap;

HashMap* create_hashmap();

bool find_by_val(const HashMap* map, int val);

int hash(int key);

void add_node(HashMap *map, int data);

void del_node(HashMap* map, int data);

void print_hash_map(const HashMap* map);
