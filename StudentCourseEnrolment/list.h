#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"
//#include "bst.h"


typedef struct listNode {
	char* course;
	AVL students; // BST students
	struct listNode* next;
} *CourseNodePtr;

typedef struct list {
	CourseNodePtr head;
} CourseList;

CourseList new_CourseList();

typedef char* String;

void print_list(CourseList* ptr);

void front_of_list_insert(CourseList* ptr, char* course);

void delete_from_list(CourseList* ptr, char* course);

void free_node(CourseList* ptr);

CourseNodePtr search_for_node(CourseNodePtr head, char* course);

void find_course_for_student(CourseNodePtr head, long student_id);


