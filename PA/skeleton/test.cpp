#include <iostream>
#include <cstring>

using namespace std;
int main()
{
    char **a = new char *[10];
    char *b = new char[10];
    memcpy(b, "hello", 10);
    *a = b;
}