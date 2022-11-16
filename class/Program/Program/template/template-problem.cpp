#include <iostream> /* File: template-problem.cpp */
using namespace std;

template <typename T>
const T &
larger(const T &a, const T &b) { return (a < b) ? b : a; }

int main()
{
    char *m = "microsoft";
    char *a = "apple";

    cout << larger(a, m) << " is better!" << endl;
    cout << larger(m, a) << " is better!" << endl;
    return 0;
}
