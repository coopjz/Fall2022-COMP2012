#include <iostream> /* File: rtti.cpp */
#include <typeinfo>
using namespace std;
#include "v-student.h"
#include "v-teacher.h"

int main()
{
    UPerson *uperson[3]{nullptr, nullptr, nullptr};
    char person_type;
    string name;

    for (int j = 0; j < sizeof(uperson) / sizeof(UPerson *); ++j)
    {
        cout << "Input the uperson type (s/t) and his name : ";
        cin >> person_type >> name;

        if (person_type == 's') // No error checking
            uperson[j] = new Student(name, CIVL, 4.0);
        else if (person_type == 't')
            uperson[j] = new Teacher(name, CSE, DEAN, "AI");
    }

    for (int j = 0; j < sizeof(uperson) / sizeof(UPerson *); ++j)
        cout << "The uperson #" << j << " is a "
             << typeid(*uperson[j]).name() << endl; // RTTI

    const type_info &t1 = typeid(*uperson[1]);
    cout << t1.hash_code();
}
