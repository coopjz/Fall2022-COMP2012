#ifndef __COURSE_DATABASE_H__
#define __COURSE_DATABASE_H__

class Course;

class Course_Database {
    private:
    Course** courses;
    int capacity;
    int size;

    public:
    Course_Database(int capacity);
    Course_Database(const Course_Database& database);
    ~Course_Database();

    bool create_entry(const char* name, int num_credit, int course_capacity);
    Course* get_course_by_name(const char* course_name) const;

    // Helper function for debugging
    void print_all_course() const;
    
    Course** get_courses();
    int get_capacity();
    int get_size();
    
    void set_courses(Course** courses);
    void set_capacity(int capacity);
    void set_size(int size);
};

#endif