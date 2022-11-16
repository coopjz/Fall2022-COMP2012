#include <iostream> /* File: template-problem.cpp */
using namespace std;

// template <typename T>
// const T &
// larger(const T &a, const T &b) { return (a < b) ? b : a; }
char *const &larger(char *const &a, char *const &b)
{
    return (a < b) ? b : a;
}
int main()
{
    const char *m = "microsoft";
    const char *a = "apple";
    int x;

    cout << &m << endl;
    cout << &a << endl;
    cout << (void *)m << endl;
    cout << (&x) << endl;

    cout << larger(a, m) << " is better!" << endl;
    cout << larger(m, a) << " is better!" << endl;
    return 0;
}
