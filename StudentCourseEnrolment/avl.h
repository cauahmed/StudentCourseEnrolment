#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct avlNode {

	long id;

	int height; //additional field for recording height of avl node

	struct avlNode* left;

	struct avlNode* right;

} *AVLNodePtr;


typedef struct avl {

	AVLNodePtr root;

} AVL;

AVL new_avl();
void empty_avl(AVLNodePtr ptr);
AVLNodePtr locate_AVL(AVL* ptr, int a);
AVLNodePtr find_minimum(AVLNodePtr ptr);
AVLNodePtr find_maximum(AVLNodePtr ptr);
void insert_into_AVL(AVL* ptr, int n);
void delete_from_AVL(AVL* ptr, int n);
void print_in_order_avl(AVL* ptr);
bool find_node(AVLNodePtr root, long id);
void delete_AVL(AVL* ptr);
int avl_tree_node_count(AVLNodePtr root);



