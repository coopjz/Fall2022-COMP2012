#include <iostream>
#include <cstring>
#include "system.h"
#include "student.h"
#include "course.h"
#include "course_database.h"
#include "student_database.h"
#include "wait_list.h"
#include "swap_list.h"

using namespace std;

/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(int student_id, Course* course) {
    
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(Student* student, const char* course_name) {
    
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(int student_id, Course* course) {
    
}


System::System(int max_num_course, int max_num_student) {
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System& system) {
    this->course_database = new Course_Database(*system.course_database);
    this->student_database = new Student_Database(*system.student_database);
}

System::~System() {
    delete course_database;
    delete student_database;
}

void System::admit(const char* name, int student_id, double gpa) {
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(int student_id, const int request_credit) {
    // TODO
}

bool System::add(int student_id, const char* course_name) {
    // TODO
}

bool System::swap(int student_id, const char* original_course_name, const char* target_course_name) {
    // TODO
}

void System::drop(int student_id, const char* course_name) {
    // TODO
}

void System::add_course(const char* name, int num_credit, int course_capacity) {
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const {
    this->course_database->print_all_course();
    this->student_database->print_all_students();
}

Course_Database* System::get_course_database() {
    return course_database;
}

Student_Database* System::get_student_database() {
    return student_database;
}

void System::set_course_database(Course_Database* course_database) {
    this->course_database = course_database;
}

void System::set_student_database(Student_Database* student_database) {
    this->student_database = student_database;
}
