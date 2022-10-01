#ifndef __STUDENT_H__
#define __STUDENT_H__

class Swap_List;

class Student {
    private:
    char* name; // A pointer to a dynamically allocated array
    int student_id;
    double gpa;
    int max_credit;
    int curr_credit;

    int num_enrolled_course;
    char** enrolled_courses; // A pointer to a 2D dynamically allocated array with the names of enrolled courses

    int pending_credit;      // The extra number of credits the student will receive if all pending swaps are enrolled successfully
    Swap_List* swap_list;    // A pointer to a dynamically allocated Swap_List object

    public:
    Student(const char* name, int student_id, double gpa);
    Student(const Student& student);
    ~Student();

    void print_info() const;

    char* get_name();
    int get_student_id();
    double get_gpa();
    int get_max_credit();
    int get_curr_credit();
    int get_num_enrolled_course();
    char** get_enrolled_courses();
    int get_pending_credit();
    Swap_List* get_swap_list();

    void set_name(char* name);
    void set_student_id(int student_id);
    void set_gpa(double gpa);
    void set_max_credit(int max_credit);
    void set_curr_credit(int curr_credit);
    void set_num_enrolled_course(int num_enrolled_course);
    void set_enrolled_courses(char** enrolled_courses);
    void set_pending_credit(int pending_credit);
    void set_swap_list(Swap_List* swap_list);
};

#endif