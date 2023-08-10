#include <stdio.h>
#include "list.h"
#include "avl.h"
//#include "bst.h"

//generate new instance of list
CourseList new_CourseList() {

	CourseList temp;

	temp.head = NULL;

	return temp;

}



void print_list(CourseList* ptr) {
	CourseNodePtr current = ptr->head;
	while (current != NULL) {
		printf("%s\t", current->course);
		printf("Current student enrolments\n");
		printf("%d\n", avl_tree_node_count(current->students.root)); //bst_tree_node_count
		current = current->next;

		if (current != NULL)
			printf("");
	}
	printf("\n");
}


void front_of_list_insert(CourseList* ptr, char* data) {


	CourseNodePtr new_Node = malloc(sizeof * new_Node);

	new_Node->course = malloc(strlen(data) + 1);

	strcpy(new_Node->course, data);
	new_Node->students = new_avl(); //new_bst()


	new_Node->next = ptr->head;
	ptr->head = new_Node;
}


void delete_from_list(CourseList* ptr, char* data) {
	CourseNodePtr current = ptr->head;
	CourseNodePtr prev = NULL;

	while (current != NULL) {
		if (strcmp(data, current->course) == 0) {
			if (prev == NULL) {        //find front of list
				ptr->head = current->next;
				free(current->course);
				delete_AVL(&current->students); //delete_bst()
				free(current); //free current node
				current = ptr->head;
			}
			else {                    //find middle of list
				prev->next = current->next;
				free(current->course);
				delete_AVL(&current->students); //delete_bst()
				free(current);//free current node
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

void free_node(CourseList* ptr) {
	CourseNodePtr current = ptr->head;
	while (current != NULL) {
		CourseNodePtr empty = current;
		current = current->next;
		free(empty->course);
		free(&empty->students);//free the data
		free(empty);//empty the node
	}
	ptr->head = NULL;
}

CourseNodePtr search_for_node(CourseNodePtr head, char* course) {
	CourseNodePtr current = head;
	while (current != NULL) {
		if ((strcmp(current->course, course)) == 0) {
			return current;
		}
		current = current->next;
	}
	printf("Course not found/n");
	return;
}

void find_course_for_student(CourseNodePtr head, long student_id) {
	CourseNodePtr current = head;
	while (current != NULL) {
		if (find_node(current->students.root, student_id) == true) { //find_node_bst()
			printf(student_id + "is enrolled in ");
			printf("\n");
			printf(current->course);
		}
		current = current->next;

	}
}