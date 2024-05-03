#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef int K;

typedef struct tree_node {
	K key;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;

typedef struct {
	TreeNode* root;
} BST;

// API

BST* bst_create();

TreeNode* bst_search(BST* tree, K key);

void bst_destroy(BST* tree);

void bst_insert(BST* tree, K key);

void bst_delete(BST* tree, K key);

void bst_preorder(BST* tree);

void bst_inorder(BST* tree);

void bst_postorder(BST* tree);

void bst_levelorder(BST* tree);