#include <iostream> /* File: construction-v-destruction-order.cpp */
using namespace std;

class Base
{
public:
  Base() { cout << "Base's constructor\n"; }
  ~Base() { cout << "Base's destructor\n"; }
};

class Derived : public Base
{
public:
  Derived() { cout << "Derived's constructor\n"; }
  ~Derived() { cout << "Derived's destructor\n"; }
};

class Derived2 : public Derived
{
public:
  Derived2() { cout << "Derived2's constructor \n"; }
  virtual ~Derived2() { cout << "Derived2's Destructor " << endl; }
};

main()
{
  Base *p = new Derived2;
  delete p;
dynamic_cast
}
