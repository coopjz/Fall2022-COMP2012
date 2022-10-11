#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode *const next) : student_id(student_id), next(next)
{
}

Wait_List::Wait_List() : head(nullptr), end(nullptr)
{
}

Wait_List::Wait_List(const Wait_List &wait_list)
{
    if (wait_list.head == nullptr)
    {
        this->head = nullptr;
        this->end = nullptr;
    }
    else
    {

        this->head = new Student_ListNode(wait_list.head->student_id, nullptr);
        this->end = this->head;
        Student_ListNode *temp = wait_list.head;
        while (temp->next)
        {
            temp = temp->next;
            this->end->next = new Student_ListNode(temp->student_id, nullptr);
            this->end = this->end->next;
        }
        this->end->next = nullptr; // check ???
    }
}
Wait_List::~Wait_List()
{
    Student_ListNode *temp = this->head;
    while (temp)
    {
        Student_ListNode *temp_student = temp;
        temp = temp->next;
        delete temp_student;
    }
    head = nullptr;
    end = nullptr;
}

void Wait_List::print_list() const
{
    Student_ListNode *temp = this->head;
    int index = 0;
    while (temp)
    {
        cout << "Waitlist Number: " << index++ << endl;
        cout << temp->student_id << endl;
        temp = temp->next;
    }
}

Student_ListNode *Wait_List::get_head() const
{
    return head;
}

Student_ListNode *Wait_List::get_end() const
{
    return end;
}

void Wait_List::set_head(Student_ListNode *const head)
{
    this->head = head;
}

void Wait_List::set_end(Student_ListNode *const end)
{
    this->end = end;
}