#include <iostream>
#include <cstring>
#include "swap_list.h"

using namespace std;

Swap::Swap(const char* original_course_name, const char* target_course_name, Swap* next) {
    // TODO
}

Swap::~Swap() {
    // TODO
}

Swap_List::Swap_List() {
    // TODO
}

Swap_List::Swap_List(const Swap_List& swap_list) {
    // TODO
}

Swap_List::~Swap_List() {
    // TODO
}

void Swap_List::print_list() const {
    Swap* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Swap: " << index++ << endl;
        cout << "Original Course: " << temp->original_course_name << endl;
        cout << "Target Course: " << temp->target_course_name << endl;
        temp = temp->next;
    }
}

Swap* Swap_List::get_head() {
    return head;
}

void Swap_List::set_head(Swap* head) {
    this->head = head;
}