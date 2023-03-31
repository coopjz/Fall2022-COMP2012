#include <iostream> /* File: static-example.cpp */
using namespace std;
#include "teacher.h"




int fun()
{
    static int a1 = 1;
}
int main()
{
    UPerson uperson("Charlie Brown", CBME);
    Teacher teacher("Alan Turing", CSE, PROFESSOR, "CS Theory");
    UPerson *u;
    Teacher *t;

    cout << "\nUPerson object pointed by UPerson pointer:\n";
    u = &uperson;
    u->print();

    cout << "\nTeacher object pointed by Teacher pointer:\n";
    t = &teacher;
    t->print();

    cout << "\nTeacher object pointed by UPerson pointer:\n";
    u = &teacher;
    u->print();
    // cout << "\nUPerson object pointed by Teacher pointer:\n";
    // t = &uperson; t->print(); // Error: convert base-class ptr
    //        to derived-class ptr
    cout << "cast____static";
    t = static_cast<Teacher *>(&uperson);
    t->print(); // Ok, but ...
}
