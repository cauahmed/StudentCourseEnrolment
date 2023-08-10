#include <stdio.h>
#include <string.h>
#include "list.h"
#include "avl.h"
//#include "bst.h"

void insert_new_course(CourseList* courselist, char* courseholder) {
	printf("Please enter course name\n");
	scanf_s("%s", courseholder, 100);
	front_of_list_insert(courselist, courseholder);
}

void remove_course(CourseList* courselist, char* courseholder) {
	printf("Please enter course name\n");
	scanf_s("%s", courseholder, 100);
	delete_from_list(courselist, courseholder);
}

void enrol_student_in_course(CourseList* courselist, long student_Id, char* courseholder) {
	CourseNodePtr find_course;
	printf("Please enter course name\n");
	scanf_s("%s", courseholder, 100);
	printf("Please enter student id\n");
	scanf_s("%d", &student_Id);
	find_course = search_for_node(courselist->head, courseholder);
	insert_into_AVL(&find_course->students, student_Id); //insert_into_BST(BST* ptr, int n)
}

void unenrol_student_in_course(CourseList* courselist, long student_Id, char* courseholder) {
	CourseNodePtr find_course;
	printf("Please enter course name\n");
	scanf_s("%s", courseholder, 100);
	printf("Please enter student id\n");
	scanf_s("%d", &student_Id);
	find_course = search_for_node(courselist->head, courseholder);
	delete_from_AVL(&find_course->students, student_Id); //delete_from_BST(BST* ptr, int n)
}

void print_course_summary(CourseList* courselist) {
	print_list(courselist);
}

void print_course_enrolment_list(CourseList* courselist, char* courseholder) {
	CourseNodePtr find_course;
	printf("Please enter course name\n");
	scanf_s("%s", courseholder, 100);
	find_course = search_for_node(courselist->head, courseholder);
	printf("The following students are enrolled in the course\n");
	print_in_order_avl(&find_course->students); //print_bst_in_order(BST* ptr)
}

void print_student_course_list(CourseList* courselist, long student_Id) {
	printf("Please enter student id\n");
	scanf_s("%d", &student_Id);
	find_course_for_student(courselist->head, student_Id);
}



int main() {

	//AVL student_tree = new_avl();
	CourseList CourseList = new_CourseList();
	char courseholder[100];
	int initiator = 1;
	long student_Id = 0;


	while (initiator) {

		printf("Please enter your selection\n");
		printf("1.Add new course\n");
		printf("2.Remove a course\n");
		printf("3.Enrol student in course\n");
		printf("4.Unenrol student from course\n");
		printf("5.Display course summary and student enrolled in each course\n");
		printf("6.Display ordered list of students enrolled in a course\n");
		printf("7.Output an ordered list of courses that a student has enrolled in\n");


		scanf_s("%d", &initiator);
		switch (initiator) {
		case 1:

			insert_new_course(&CourseList, &courseholder);

			break;

		case 2:

			remove_course(&CourseList, &courseholder);

			break;

		case 3:

			enrol_student_in_course(&CourseList, &student_Id, &courseholder);

			break;

		case 4:

			unenrol_student_in_course(&CourseList, &student_Id, &courseholder);

			break;
		case 5:

			print_course_summary(&CourseList);

			break;
		case 6:

			print_course_enrolment_list(&CourseList, &courseholder);

			break;
		case 7:

			print_student_course_list(&CourseList, &student_Id);

			break;

		}

		printf("\n");


	}




}