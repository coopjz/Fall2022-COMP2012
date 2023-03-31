#include <iostream>
using namespace std;
class Base
{
public:
    virtual void print() const
    {
        cout << "Base" << endl;
    }
};
class Derived : public Base
{
public:
    void print() const
    {
        std::forward();
        cout << "Derived" << endl;
    }
};
class Derived2 : public Derived
{
public:
    void print() const
    {
        cout << "Derived2" << endl;
    }
};
int main()
{
    Base *b = new Derived2();
    b->print();
    return 0;
}