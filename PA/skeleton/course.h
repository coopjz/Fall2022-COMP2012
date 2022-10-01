#ifndef __COURSE_H__
#define __COURSE_H__

class Student_ListNode;
class Wait_List;

class Course {
    private:
    char* name;
    int num_credit;
    int capacity;
    int size;
    Wait_List* wait_list;
    int* students_enrolled;
    
    public:
    Course(const char* name, int num_credit, int course_capacity);
    Course(const Course& course);
    ~Course();

    void print_info() const;

    char* get_name();
    int get_num_credit();
    int get_capacity();
    int get_size();
    Wait_List* get_wait_list();
    int* get_students_enrolled();

    void set_name(char* name);
    void set_num_credit(int num_credit);
    void set_capacity(int capacity);
    void set_size(int size);
    void set_wait_list(Wait_List* wait_list);
    void set_students_enrolled(int* students_enrolled);    
};

#endif