#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct bstNode {

	long id;

	struct bstNode* left;

	struct bstNode* right;

} *BSTNodePtr;


typedef struct bst {

	BSTNodePtr root;

} BST;

BST new_bst();

void insert_into_BST(BST* ptr, int n);

void delete_from_BST(BST* ptr, int n);

void delete_bst(BST* ptr);

void print_bst_in_order(BST* ptr);

BSTNodePtr find_node_bst(BSTNodePtr ptr, int n);

BSTNodePtr find_bst(BST* ptr, int n);

bool find_node_bst_bool(BSTNodePtr root, long id);

int bst_tree_node_count(BSTNodePtr root);







