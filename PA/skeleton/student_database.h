#ifndef __STUDENT_DATABASE_H__
#define __STUDENT_DATABASE_H__

class Student;

class Student_Database {
    private:
    Student** students;
    int capacity;
    int size;

    public:
    Student_Database(int capacity);
    Student_Database(const Student_Database& database);
    ~Student_Database();

    bool create_entry(const char* name, int student_id, double gpa);
    Student* get_student_by_id(int student_id) const;
    
    // Helper function for debugging
    void print_all_students() const;

    Student** get_students();
    int get_capacity();
    int get_size();

    void set_students(Student** students);
    void set_capacity(int capacity);
    void set_size(int size);
};

#endif