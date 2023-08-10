//relevant definitions adapted based on material from https://www.geeksforgeeks.org/binary-search-tree-data-structure/
//additional functions present which have not been utilized
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

//create new bst structure
BST new_bst() {
	BST new;

	new.root = NULL;

	return new;
}

//boolean result to reply if node is found
bool find_node_bst_bool(BSTNodePtr root, long id) {
	bool comp_result = false;
	BSTNodePtr current = root;


	if (current != NULL) {
		find_node(current->left, id);
		comp_result = (current->id == id);
		find_node(current->right, id);
	}
	return comp_result;
}

//delete the entire bst
void delete_bst(BST* ptr) {

	if (ptr->root != NULL)
	{
		delete_bst(ptr->root->left);
		delete_bst(ptr->root->right);
		free(ptr);
	}
}

//count number of nodes in the bst
int bst_tree_node_count(BSTNodePtr root) {
	if (root == NULL) {
		return 0;
	}
	int count = 1;
	if (root->left != NULL) {
		count += bst_tree_node_count(root->left);
	}
	if (root->right != NULL) {
		count += bst_tree_node_count(root->right);
	}
	return count;
}

//find single node in bst and return it
BSTNodePtr find_node_bst(BSTNodePtr ptr, int n) {

	if (ptr == NULL || (n == ptr->id)) {

		return ptr;

	}
	else if (n < ptr->id) {

		return find_node_bst(ptr->left, n);

	}
	else {

		return find_node_bst(ptr->right, n);

	}

}


//find node in bst recursively for entire bst
BSTNodePtr find_bst(BST* ptr, int n) {
	return find_node_bst(ptr->root, n);
}

//insert a node in a bst
BSTNodePtr bst_insert_node(BSTNodePtr ptr, int n) {

	if (ptr == NULL) {

		ptr = malloc(sizeof * ptr);

		ptr->id = n;

		ptr->left = NULL;

		ptr->right = NULL;

	}
	else if (n < ptr->id) {

		ptr->left = bst_insert_node(ptr->left, n);

	}
	else if (n > ptr->id) {

		ptr->right = bst_insert_node(ptr->right, n);

	}

	return ptr;
}

//start insert from root position
void insert_into_BST(BST* ptr, int n) {
	ptr->root = bst_insert_node(ptr->root, n);
}


//find minimim node in the bst tree
BSTNodePtr find_min_node(BSTNodePtr ptr) {
	BSTNodePtr current = ptr;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}


//delete node from bst
BSTNodePtr bst_delete_node(BSTNodePtr ptr, int n) {
	if (ptr != NULL) {
		if (n == ptr->id) {
			if (ptr->left != NULL && ptr->right != NULL) {

				BSTNodePtr replacer = find_min_node(ptr->right); //find minimum node in trr
				ptr->id = replacer->id;
				ptr->right = bst_delete_node(ptr->right, ptr->id);
			}
			else {
				BSTNodePtr toberemoved = ptr;
				if (ptr->left) {
					ptr = ptr->left;
				}
				else {
					ptr = ptr->right;
				}
				free(toberemoved);
			}

		}
		else if (n < ptr->id) {
			ptr->left = bst_delete_node(ptr->left, n);
		}
		else {
			ptr->right = bst_delete_node(ptr->right, n);
		}
	}
	return ptr;
}

//start deletion from root
void delete_from_BST(BST* ptr, int n) {
	ptr->root = bst_delete_node(ptr->root, n);
}


//print bst nodes in order
void print_bst_node_in_order(BSTNodePtr ptr) {
	if (ptr != NULL) {
		printf("\n");
		print_bst_node_in_order(ptr->left);
		printf("%d", ptr->id);
		print_bst_node_in_order(ptr->right);
		printf("");
	}
	else {
		printf("");
	}
}

//initiate print from root
void print_bst_in_order(BST* ptr) {
	print_bst_node_in_order(ptr->root);
}



