#ifndef __STUDENT_LISTNODE_H__
#define __STUDENT_LISTNODE_H__

class Student_ListNode {
    public:
    int student_id;
    Student_ListNode* next;

    Student_ListNode(int student_id, Student_ListNode* next);
    ~Student_ListNode() = default;
};

class Wait_List {
    private:
    Student_ListNode* head;
    Student_ListNode* end;

    public:
    Wait_List();
    Wait_List(const Wait_List& wait_list);
    ~Wait_List();

    void print_list() const;

    Student_ListNode* get_head();
    Student_ListNode* get_end();

    void set_head(Student_ListNode* head);
    void set_end(Student_ListNode* end);
};

#endif