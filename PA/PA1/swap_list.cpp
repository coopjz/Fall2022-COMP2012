#include <iostream>
#include <cstring>
#include "swap_list.h"

using namespace std;

Swap::Swap(const char *const original_course_name, const char *const target_course_name, Swap *const next)
{
    // TODO
    this->original_course_name = new char[strlen(original_course_name) + 1]();
    strcpy(this->original_course_name, original_course_name);
    this->target_course_name = new char[strlen(target_course_name) + 1]();
    strcpy(this->target_course_name, target_course_name);
    this->next = next;
}

Swap::~Swap()
{
    // TODO
    delete[] this->original_course_name;
    delete[] this->target_course_name;
}

Swap_List::Swap_List()
{
    this->head = nullptr;
}

Swap_List::Swap_List(const Swap_List &swap_list)
{
    // TODO
    if (swap_list.head == nullptr)
    {
        this->head = nullptr;
    }
    else
    {
        Swap *temp_swap = swap_list.head;
        this->head = new Swap(swap_list.head->original_course_name, swap_list.head->target_course_name, nullptr);
        Swap *temp = this->head;
        while (temp_swap->next)
        {
            temp_swap = temp_swap->next;
            temp->next = new Swap(temp_swap->original_course_name, temp_swap->target_course_name, nullptr);
            temp = temp->next;
        }
    }
}

Swap_List::~Swap_List()
{
    // TODO
    Swap *temp = this->head;
    while (temp)
    {
        Swap *temp_swap = temp;
        temp = temp->next;
        delete temp_swap;
    }
}

void Swap_List::print_list() const
{
    Swap *temp = this->head;
    int index = 0;
    while (temp)
    {
        cout << "Swap: " << index++ << endl;
        cout << "Original Course: " << temp->original_course_name << endl;
        cout << "Target Course: " << temp->target_course_name << endl;
        temp = temp->next;
    }
}

Swap *Swap_List::get_head() const
{
    return head;
}

void Swap_List::set_head(Swap *const head)
{
    this->head = head;
}