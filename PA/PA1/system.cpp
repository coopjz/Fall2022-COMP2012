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
#define ABS(x) x < 0 ? -x : x
/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(const int student_id, Course *course)
{
    // TODO
    if (course->get_wait_list()->get_head() == nullptr)
    {
        course->get_wait_list()->set_head(new Student_ListNode(student_id, nullptr));
        course->get_wait_list()->set_end(course->get_wait_list()->get_head());
    }
    else
    {
        course->get_wait_list()->get_end()->next = new Student_ListNode(student_id, nullptr);
        course->get_wait_list()->set_end(course->get_wait_list()->get_end()->next);
    }
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(const Student *const student, const char *const course_name)
{
    char **course = student->get_enrolled_courses();
    // while (course++)
    // {
    //     if (*course == nullptr)
    //     {
    //         return -1;
    //     }
    //     if (!strcmp(*course, course_name))
    //     {
    //         return course - student->get_enrolled_courses();
    //     }
    // }
    for (int i = 0; i < student->get_num_enrolled_course(); i++)
    {
        if (!strcmp(course[i], course_name))
        {
            return i;
        }
    }
    return -1;
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course *const course)
{
    int *student = course->get_students_enrolled();
    // while (student++)
    // {
    //     if (student == nullptr)
    //     {
    //         return -1;
    //     }
    //     if (*student == student_id)
    //     {
    //         return student - course->get_students_enrolled();
    //     }
    // }
    for (int i = 0; i < course->get_size(); i++)
    {
        if (student[i] == student_id)
        {
            return i;
        }
    }
    return -1;
}

// int worst_case_swap(const Swap_List *const Swap_list)
// {
//     int max = 0;
//     Swap *temp = Swap_list->get_head();
//     while (temp)
//     {
//         temp->original_course_name
//         temp = temp->get_next();
//     }
// }

System::System(const int max_num_course, const int max_num_student)
{
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System &system)
{
    this->course_database = new Course_Database(*system.course_database);
    this->student_database = new Student_Database(*system.student_database);
}

System::~System()
{
    delete course_database;
    delete student_database;
}

void System::admit(const char *const name, const int student_id, const double gpa)
{
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(const int student_id, const int request_credit)
{
    // TODO
    Student *student_apply = this->student_database->get_student_by_id(student_id);
    if (student_apply == nullptr)
    {
        return false;
    }
    if (request_credit > 30)
        return false;
    else if (request_credit > 24 || request_credit == 24)
    {
        if (student_apply->get_gpa() > 3.7)
        {
            student_apply->set_max_credit(request_credit);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (request_credit > 18 || request_credit == 18)
    {
        if (student_apply->get_gpa() > 3.3)
        {
            student_apply->set_max_credit(request_credit);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool System::add(const int student_id, const char *const course_name)
{
    Student *student_apply = this->student_database->get_student_by_id(student_id);
    Course *course_apply = this->course_database->get_course_by_name(course_name);
    int cur_credit = student_apply->get_curr_credit();
    int add_credit = course_apply->get_num_credit();
    int pending_credit = student_apply->get_pending_credit();
    if ((cur_credit + pending_credit + add_credit) < student_apply->get_max_credit() || (cur_credit + pending_credit + add_credit) == student_apply->get_max_credit())
    {
        if (course_apply->get_size() < course_apply->get_capacity())
        {
            int *student_list = course_apply->get_students_enrolled();
            student_list[course_apply->get_size()] = student_id;
            course_apply->set_students_enrolled(student_list);

            course_apply->set_size(course_apply->get_size() + 1);

            char **enrolled_courses = student_apply->get_enrolled_courses();
            enrolled_courses[student_apply->get_num_enrolled_course()] = new char[strlen(course_name) + 1]();
            strcpy(*(enrolled_courses + student_apply->get_num_enrolled_course()), course_name);
            student_apply->set_enrolled_courses(enrolled_courses);
            student_apply->set_num_enrolled_course(student_apply->get_num_enrolled_course() + 1);
            student_apply->set_curr_credit(student_apply->get_curr_credit() + add_credit);
            return true;
        }
        else
        {
            join_waitlist(student_id, course_apply);
            pending_credit += add_credit;
            student_apply->set_pending_credit(pending_credit);
            return true;
        }
    }
    else
    {
        return false;
    }
    return false;
    // int waitlist_credit = get wait list credits of this students.
    // int swap list credit = get max swap list credit.(swap>unswap?swap:unswap)
    // pending credit = waitlist cre+ swaplist cre
    // if (cur_credit + pending credit + course credit > max credit)
    //      return false;
    // int swap_list_credit = 0;
}

bool System::swap(const int student_id, const char *const original_course_name, const char *const target_course_name)
{
    Student *student_apply = this->student_database->get_student_by_id(student_id);
    Course *original_course = this->course_database->get_course_by_name(original_course_name);
    Course *target_course = this->course_database->get_course_by_name(target_course_name);
    int cur_credit = student_apply->get_curr_credit();
    int add_credit = target_course->get_num_credit();
    int original_credit = original_course->get_num_credit();
    int pending_credit = student_apply->get_pending_credit();
    int credit_diff = add_credit - original_credit;
    if ((cur_credit + pending_credit + credit_diff) < student_apply->get_max_credit() || (cur_credit + pending_credit + credit_diff) == student_apply->get_max_credit())
    {
        if (target_course->get_capacity() > target_course->get_size())
        {
            int *student_list = target_course->get_students_enrolled();
            student_list[target_course->get_size()] = student_id;
            target_course->set_students_enrolled(student_list);

            target_course->set_size(target_course->get_size() + 1);

            char **enrolled_courses = student_apply->get_enrolled_courses();
            *(enrolled_courses + student_apply->get_num_enrolled_course()) = new char[strlen(target_course_name) + 1]();
            strcpy(*(enrolled_courses + student_apply->get_num_enrolled_course()), target_course_name);

            student_apply->set_num_enrolled_course(student_apply->get_num_enrolled_course() + 1);
            this->drop(student_id, original_course_name);
            student_apply->set_curr_credit(student_apply->get_curr_credit() + add_credit);
        }
        else
        {
            join_waitlist(student_id, target_course);
            pending_credit += (original_credit > add_credit ? 0 : add_credit - original_credit);
            student_apply->set_pending_credit(pending_credit);

            Swap_List *swap_list = student_apply->get_swap_list();

            Swap *swap = new Swap(original_course_name, target_course_name, nullptr);
            if (swap_list->get_head() == nullptr)
            {
                swap_list->set_head(swap);
            }
            else
            {
                swap->next = swap_list->get_head();
                swap_list->set_head(swap);
            }
            student_apply->set_swap_list(swap_list);
        }
        return true;
    }
    else
        return false;
}

void add_in_drop(Student *wait_student, Course *course, const int add_index)
{
    int cur_credit = wait_student->get_curr_credit();
    int add_credit = course->get_num_credit();
    int pending_credit = wait_student->get_pending_credit();
    int *student_list = course->get_students_enrolled();
    student_list[add_index] = wait_student->get_student_id();
    course->set_students_enrolled(student_list);
    char **enrolled_courses = wait_student->get_enrolled_courses();
    enrolled_courses[wait_student->get_num_enrolled_course()] = new char[strlen(course->get_name()) + 1]();
    strcpy(*(enrolled_courses + wait_student->get_num_enrolled_course()), course->get_name());
    wait_student->set_enrolled_courses(enrolled_courses);
    wait_student->set_num_enrolled_course(wait_student->get_num_enrolled_course() + 1);
    wait_student->set_curr_credit(wait_student->get_curr_credit() + add_credit);
    wait_student->set_pending_credit(pending_credit - add_credit);
}

void System::drop(const int student_id, const char *const course_name)
{
    // TODO
    Student *student_apply = this->get_student_database()->get_student_by_id(student_id);
    Course *drop_course = this->get_course_database()->get_course_by_name(course_name);
    int drop_course_index = search_course_index(student_apply, course_name);
    char **couse_list = student_apply->get_enrolled_courses();
    if (student_apply->get_num_enrolled_course() == (drop_course_index + 1))
    {
        delete[] * (student_apply->get_enrolled_courses() + drop_course_index);
        *(student_apply->get_enrolled_courses() + student_apply->get_num_enrolled_course() - 1) = nullptr;
    }
    else
    {

        delete[] * (student_apply->get_enrolled_courses() + drop_course_index);
        *(student_apply->get_enrolled_courses() + drop_course_index) = *(student_apply->get_enrolled_courses() + student_apply->get_num_enrolled_course() - 1);
        *(student_apply->get_enrolled_courses() + student_apply->get_num_enrolled_course() - 1) = nullptr;
    }
    student_apply->set_num_enrolled_course(student_apply->get_num_enrolled_course() - 1);
    student_apply->set_curr_credit(student_apply->get_curr_credit() - drop_course->get_num_credit());
    student_apply->set_enrolled_courses(couse_list); // redundeant????

    // due with drop course part
    int drop_student_index = search_student_id(student_id, drop_course);

    // *(drop_course->get_students_enrolled() + drop_student_index) = *(drop_course->get_students_enrolled() + drop_course->get_size() - 1);
    // drop_course->get_students_enrolled()[drop_course->get_size() - 1] = 0;
    // drop_course->set_size(drop_course->get_size() - 1);

    if (drop_course->get_wait_list()->get_head() != nullptr)
    {
        int wait_student_id = drop_course->get_wait_list()->get_head()->student_id;
        Student *wait_student = this->get_student_database()->get_student_by_id(wait_student_id);
        /////////////////////////////////
        Student_ListNode *temp = drop_course->get_wait_list()->get_head();

        if (temp->next != nullptr)
            drop_course->get_wait_list()->set_head(temp->next);
        else
        {
            drop_course->get_wait_list()->set_head(nullptr);
            drop_course->get_wait_list()->set_end(nullptr);
        }
        delete temp;
        temp = nullptr;
        //////////////////////////////////
        if (wait_student->get_swap_list()->get_head() == nullptr)
        {

            add_in_drop(wait_student, drop_course, drop_student_index);
        }
        else
        {

            Swap *temp_swap = wait_student->get_swap_list()->get_head();
            bool isswap = false;
            while (temp_swap)
            {
                if (!strcmp(temp_swap->target_course_name, course_name))
                {

                    int cur_credit = wait_student->get_curr_credit();
                    int add_credit = drop_course->get_num_credit();
                    int drop_credit = this->get_course_database()->get_course_by_name(temp_swap->original_course_name)->get_num_credit();
                    // course
                    int *student_list = drop_course->get_students_enrolled();
                    int credit_diff = -drop_credit + add_credit;
                    student_list[drop_student_index] = wait_student->get_student_id();
                    drop_course->set_students_enrolled(student_list);

                    char **enrolled_courses = wait_student->get_enrolled_courses();
                    *(enrolled_courses + wait_student->get_num_enrolled_course()) = new char[strlen(drop_course->get_name()) + 1]();
                    strcpy(*(enrolled_courses + wait_student->get_num_enrolled_course()), drop_course->get_name());

                    wait_student->set_num_enrolled_course(wait_student->get_num_enrolled_course() + 1);
                    // Student_ListNode *temp = drop_course->get_wait_list()->get_head();

                    // if (temp->next != nullptr)
                    //     drop_course->get_wait_list()->set_head(temp->next);
                    // else
                    // {
                    //     drop_course->get_wait_list()->set_head(nullptr);
                    //     drop_course->get_wait_list()->set_end(nullptr);
                    // }
                    // delete temp;
                    // temp = nullptr;
                    this->drop(wait_student->get_student_id(), temp_swap->original_course_name);

                    int pending_credit = wait_student->get_pending_credit();
                    wait_student->set_curr_credit(wait_student->get_curr_credit() + add_credit);
                    pending_credit -= (drop_credit > add_credit ? 0 : add_credit - drop_credit);
                    wait_student->set_pending_credit(pending_credit);
                    isswap = true;
                    break;
                }
                temp_swap = temp_swap->next;
            }
            if (!isswap)
                add_in_drop(wait_student, drop_course, drop_student_index);
            else
            {
                if (temp_swap == wait_student->get_swap_list()->get_head())
                {
                    if (temp_swap->next == nullptr)
                    {
                        wait_student->get_swap_list()->set_head(nullptr);
                    }
                    else
                    {
                        wait_student->get_swap_list()->set_head(temp_swap->next);
                    }
                    delete temp_swap;
                }
                else
                {
                    Swap *temp_swap2 = wait_student->get_swap_list()->get_head();
                    while (temp_swap2->next != temp_swap)
                    {
                        temp_swap2 = temp_swap2->next;
                    }
                    temp_swap2->next = temp_swap->next;
                    delete temp_swap;
                }
            }
        }
        // if (drop_course->get_wait_list()->get_head() != nullptr)
        // {

        //     Student_ListNode *temp = drop_course->get_wait_list()->get_head();

        //     if (temp->next != nullptr)
        //         drop_course->get_wait_list()->set_head(temp->next);
        //     else
        //     {
        //         drop_course->get_wait_list()->set_head(nullptr);
        //         drop_course->get_wait_list()->set_end(nullptr);
        //     }
        //     delete temp;
        //     temp = nullptr;
        // }
    }
    else
    {
        *(drop_course->get_students_enrolled() + drop_student_index) = *(drop_course->get_students_enrolled() + drop_course->get_size() - 1);
        drop_course->get_students_enrolled()[drop_course->get_size() - 1] = 0;
        drop_course->set_size(drop_course->get_size() - 1);
    }
}

void System::add_course(const char *const name, const int num_credit, const int course_capacity)
{
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const
{
    this->course_database->print_all_course();
    this->student_database->print_all_students();
}

Course_Database *System::get_course_database() const
{
    return course_database;
}

Student_Database *System::get_student_database() const
{
    return student_database;
}

void System::set_course_database(Course_Database *const course_database)
{
    this->course_database = course_database;
}

void System::set_student_database(Student_Database *const student_database)
{
    this->student_database = student_database;
}
