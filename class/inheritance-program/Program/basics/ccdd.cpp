#include <iostream>
using namespace std;

class Table
{
public:
    Table() { cout << "T" << endl; }
    ~Table() { cout << "~T" << endl; }
};

class Chair
{
public:
    Chair() { cout << "C" << endl; }
    ~Chair() { cout << "~C" << endl; }
};

class Whiteboard
{
public:
    Whiteboard() { cout << "W" << endl; }
    ~Whiteboard() { cout << "~W" << endl; }
};

class Room
{
    Table *tables;
    Chair *chairs;
    Whiteboard *whiteboards;
    int numT, numC, numW;

public:
    Room(int numT, int numC, int numW) : whiteboards(new Whiteboard[numW]),
                                         chairs(new Chair[numC]), tables(new Table[numT])
    {
        this->numT = numT;
        this->numC = numC;
        this->numW = numW;
        cout << "R Other" << endl;
    }
    Room(const Room &r)
    {
        tables = new Table[r.numT];
        this->numT = r.numT;
        chairs = new Chair[r.numC];
        this->numC = r.numC;
        whiteboards = new Whiteboard[r.numW];
        this->numW = r.numW;
        cout << "R Copy" << endl;
    }
    ~Room()
    {
        delete[] tables;
        delete[] chairs;
        delete[] whiteboards;
        cout << "~R" << endl;
    }
};

int main() { Room miniRoom = *(new Room(1, 2, 1)); }
