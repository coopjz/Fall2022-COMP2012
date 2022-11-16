class A
{
    int x;

public:
    A(const A &a){};
};
int main()
{
    const int **ptr1 = new const int *;
    *ptr1 = new int;

    return 0;
}