#include "iostream"
#include <cstring>
#include "course.h"
#include "wait_list.h"

using namespace std;

Course::Course(const char* name, int num_credit, int course_capacity) {
    // TODO
}

Course::Course(const Course& course) {
    // TODO
}

Course::~Course() {
    // TODO
}

void Course::print_info() const {
    cout << "---------------------" << endl;
    cout << "Course Name: " << this->name << endl;
    cout << "Num Credit: " << this->num_credit << endl;
    cout << "Current Size: " << this->size << " out of Capacity: " << this->capacity << endl;
    cout << endl;
    cout << "Student Enrolled: " << endl;
    for(int i = 0; i < this->size; ++i) {
        cout << this->students_enrolled[i] << endl;
    }
    cout << endl;
    cout << "Waitlist Information: " << endl;
    this->wait_list->print_list();
    cout << endl;
}

char* Course::get_name() {
    return name;
}

int Course::get_num_credit() {
    return num_credit;
}

int Course::get_capacity() {
    return capacity;
}

int Course::get_size() {
    return size;
}

Wait_List* Course::get_wait_list() {
    return wait_list;
}

int* Course::get_students_enrolled() {
    return students_enrolled;
}

void Course::set_name(char* name) {
    this->name = name;
}

void Course::set_num_credit(int num_credit) {
    this->num_credit = num_credit;
}

void Course::set_capacity(int capacity) {
    this->capacity = capacity;
}

void Course::set_size(int size) {
    this->size = size;
}

void Course::set_wait_list(Wait_List* wait_list) {
    this->wait_list = wait_list;
}

void Course::set_students_enrolled(int* students_enrolled){
    this->students_enrolled = students_enrolled;
}