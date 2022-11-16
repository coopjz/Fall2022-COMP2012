class A
{
public:
    const int &getA() const
    {
        return a;
    }
    int cal(int b) const
    {
        return getA() + b;
    }

private:
    const int a{10};
};