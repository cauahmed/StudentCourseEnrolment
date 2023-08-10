//AVL deletion adapted from https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
//Maximim, minimum, height calculation and rotation adapted from http://www.zentut.com/c-tutorial/c-avl-tree/
//additional functions present such as min and max which have not been utilized

#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



//new avl instance
AVL new_avl() {
	AVL new;

	new.root = NULL;

	return new;
}

//remove all nodes of the avl tree
void empty_avl(AVLNodePtr ptr)
{
	if (ptr != NULL)
	{
		empty_avl(ptr->left);
		empty_avl(ptr->right);
		free(ptr);
	}
}

//find minimum node
AVLNodePtr find_minimum(AVLNodePtr ptr) {
	if (ptr == NULL) {
		return NULL;
	}
	else if (ptr->left == NULL) {
		return ptr;
	}
	else {
		return find_minimum(ptr->left);
	}
}

//find maximum node
AVLNodePtr find_maximum(AVLNodePtr ptr) {
	if (ptr != NULL) {
		while (ptr->right != NULL) {
			ptr = ptr->right;
		}
		return ptr;
	}
}

//return height of node
int calculateheight(AVLNodePtr ptr) {
	if (ptr == NULL) {
		return -1;
	}
	else {
		return ptr->height;
	}
}


//perform single rotation between given node and its left child node
AVLNodePtr rotate_left_node_single(AVLNodePtr n) {
	AVLNodePtr n1 = NULL;
	n1 = n->left;
	n->left = n1->right;
	n1->right = n;
	n->height = max(calculateheight(n->left), calculateheight(n->right));
	n1->height = max(calculateheight(n1->left), n->height) + 1;
	return n1; //new root after rotation is completed


}

//perform single rotation between given node and its right child
AVLNodePtr rotate_right_node_single(AVLNodePtr n) {
	AVLNodePtr n2 = NULL;
	n2 = n->right;
	n->right = n2->left;
	n2->left = n;
	n->height = max(calculateheight(n->left), calculateheight(n->right));
	n2->height = max(calculateheight(n2->right), n->height) + 1;
	return n2; //new root after rotation is completed
}

//carry out left-right double rotation
AVLNodePtr rotate_left_double(AVLNodePtr n3) {

	//Rotate between n1 and n2
	n3->left = rotate_right_node_single(n3->left);

	/* Rotate between n3 and n2 */
	return rotate_left_node_single(n3);
}

//carry out right-left double rotation
AVLNodePtr rotate_right_double(AVLNodePtr n1)
{
	/* rotate between n3 and n2 */
	n1->right = rotate_left_node_single(n1->right);

	/* rotate between n1 and n2 */
	return rotate_right_node_single(n1);
}

//locate a specific node ptr using data input
AVLNodePtr locate_avl_node(AVLNodePtr ptr, int a) {

	if (ptr == NULL || (a == ptr->id)) {

		return ptr;

	}
	else if (a < ptr->id) {

		return locate_avl_node(ptr->left, a);

	}
	else {

		return locate_avl_node(ptr->right, a);

	}

}

//locate the entire avl by locating nodes recursively
AVLNodePtr locate_AVL(AVL* ptr, int a) {
	return locate_avl_node(ptr->root, a);
}


//calculate balancing factor of given avl
int generate_balance_factor(AVLNodePtr ptr, bool l2r)
{
	if (ptr == NULL) {
		return 0;
	}
	int bfl2r = calculateheight(ptr->left) - calculateheight(ptr->right);
	int bfr2l = calculateheight(ptr->right) - calculateheight(ptr->left);

	if (l2r == true) {
		return bfl2r;
	}
	else {
		return bfr2l;
	}
}

//insert node in avl tree
AVLNodePtr insert_avl_node(AVLNodePtr ptr, int n) {

	if (ptr == NULL) { //return a one node tree upon finding a null avl

		ptr = malloc(sizeof * ptr);

		ptr->id = n;

		ptr->height = 0;

		ptr->left = ptr->right = NULL;

	}
	else if (n < ptr->id) {

		ptr->left = insert_avl_node(ptr->left, n);
		if (generate_balance_factor(ptr, true) == 2) {
			if (n < ptr->left->id) {
				ptr = rotate_left_node_single(ptr);
			}
			else {
				ptr = rotate_left_double(ptr);
			}
		}

	}
	else if (n > ptr->id) {

		ptr->right = insert_avl_node(ptr->right, n);
		if (generate_balance_factor(ptr, false) == 2) {
			if (n > ptr->right->id) {
				ptr = rotate_right_node_single(ptr);
			}
			else {
				ptr = rotate_right_double(ptr);
			}
		}

	}

	//othwise, node already exists in tree
	ptr->height = max(calculateheight(ptr->left), calculateheight(ptr->right));
	return ptr;
}

//perform insertion in a avl tree by recusively calling insert_avl_node
void insert_into_AVL(AVL* ptr, int n) {
	ptr->root = insert_avl_node(ptr->root, n);
}






//delete given node in an AVL tree
AVLNodePtr avl_delete_node(AVLNodePtr ptr, int n) {
	if (ptr == NULL) {
		return ptr;
	}

	if (n < ptr->id) {
		ptr->left = avl_delete_node(ptr->left, n);
	}
	else if (n > ptr->id) {
		ptr->right = avl_delete_node(ptr->right, n);
	}
	else {
		if (ptr->left != NULL && ptr->right != NULL) {
			// case with two childs 
			AVLNodePtr replacer = find_minimum(ptr->right);
			ptr->id = replacer->id;
			ptr->right = avl_delete_node(ptr->right, ptr->id);
		}
		else {
			// case with one or zero child 
			AVLNodePtr empty = ptr;
			if (ptr->left) {
				ptr = ptr->left;
			}
			else {
				ptr = ptr->right;
			}
			free(empty);
		}
	}

	if (ptr == NULL) {
		return ptr;
	}

	ptr->height = max(calculateheight(ptr->left), calculateheight(ptr->right)) + 1;

	int balance_factor = generate_balance_factor(ptr, true);

	if (generate_balance_factor(ptr->left, true) && balance_factor > 1 >= 0) {
		return rotate_right_node_single(ptr);
	}

	if (generate_balance_factor(ptr->left, true) && balance_factor > 1 < 0) {
		ptr->left = rotate_left_node_single(ptr->left);
		return rotate_right_node_single(ptr);

	}

	if (generate_balance_factor(ptr->right, true) && balance_factor < -1 <= 0) {
		return rotate_left_node_single(ptr);
	}

	if (generate_balance_factor(ptr->right, true) && balance_factor < -1  > 0)
	{
		ptr->right = rotate_right_node_single(ptr->right);
		return rotate_left_node_single(ptr);
	}

	return ptr;
}



//perform deletion by recursively calling avl_delete_node
void delete_from_AVL(AVL* ptr, int n) {
	ptr->root = avl_delete_node(ptr->root, n);
}

void print_in_order_avl_node(AVLNodePtr ptr) {
	if (ptr != NULL) {
		printf("(");

		print_in_order_avl_node(ptr->left);
		printf(" %d ", ptr->id);
		print_in_order_avl_node(ptr->right);
		printf(")");
	}
	else {
		printf("_");
	}
}

void print_in_order_avl(AVL* ptr) {
	print_in_order_avl_node(ptr->root);
}


int avl_tree_node_count(AVLNodePtr root) {
	if (root == NULL) {
		return 0;
	}
	int count = 1;
	if (root->left != NULL) {
		count += avl_tree_node_count(root->left);
	}
	if (root->right != NULL) {
		count += avl_tree_node_count(root->right);
	}
	return count;
}

bool find_node(AVLNodePtr root, long id) {
	bool comp_result = false;
	AVLNodePtr current = root;


	if (current != NULL) {
		find_node(current->left, id);
		comp_result = (current->id == id);
		find_node(current->right, id);
	}
	return comp_result;
}

void delete_AVL(AVL* ptr) {
	if (ptr->root == NULL) {
		return;
	}
	delete_AVL(ptr->root->left);
	delete_AVL(ptr->root->right);
	free(ptr);

}



