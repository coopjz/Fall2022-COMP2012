#ifndef __SYSTEM_H__
#define __SYSTEM_H__

class Course_Database;
class Student_Database;

class System {
    private:
    Course_Database* course_database;
    Student_Database* student_database;

    public:
    System(int max_num_course, int max_num_student);
    System(const System& system);
    ~System();

    // Student related functions
    void admit(const char* name, int student_id, double gpa);
    bool apply_overload(int student_id, int request_credit);
    bool add(int student_id, const char* course_name);
    bool swap(int student_id, const char* original_course_name, const char* target_course_name); // Always assume that student has enrolled into the original course
    void drop(int student_id, const char* course_name); // Assume student always has the course to drop
    
    // Course related functions
    void add_course(const char* name, int num_credit, int max_capacity);
    
    void print_info() const;

    Course_Database* get_course_database();
    Student_Database* get_student_database();

    void set_course_database(Course_Database* course_database);
    void set_student_database(Student_Database* student_database);
};

#endif