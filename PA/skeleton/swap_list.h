#ifndef __SWAP_H__
#define __SWAP_H__

class Swap {
    public:
    char* original_course_name;
    char* target_course_name;
    Swap* next;

    Swap(const char* original_course_name, const char* target_course_name, Swap* next);
    ~Swap();
};

// Swap List is a wrapper for Swap, the purpose is to make the copy constructor meaningful
class Swap_List{
    private:
    Swap* head;

    public:
    Swap_List();
    Swap_List(const Swap_List& swap_list);
    ~Swap_List();

    void print_list() const;

    Swap* get_head();
    void set_head(Swap* head);
};

#endif