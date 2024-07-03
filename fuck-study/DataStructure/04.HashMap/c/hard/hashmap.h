#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#define DEFAULT_CAPACITY 8
#define DEFAULT_LOAD_FACTOR 0.75f

typedef char* K;

typedef char* V;

typedef struct node {
	K key;
	V val;
	struct node* next;
} Node;

typedef struct {
	Node** table;
	int size;
	int capacity;
	uint32_t hashseed;
} HashMap;

HashMap* hashmap_create();

void hashmap_destroy(HashMap* map);

V hashmap_put(HashMap* map, K key, V val);

V hashmap_get(HashMap* map, K key);

void hashmap_delete(HashMap* map, K key);

void print_hashmap(const HashMap* map);