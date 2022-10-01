#include <iostream>
#include "string.h"
using namespace std;
class Word
{
private:
  int frequency;
  char *str;

public:
  Word(char c)
  {
    frequency = 1;
    str = new char[2];
    str[0] = c;
    str[1] = '\0';
    cout << "call implicit char conversion\n";
  }
  Word(const char *s)
  {
    frequency = 1;
    str = new char[strlen(s) + 1];
    strcpy(str, s);
    cout << "call implicit const char* conversion\n";
  }
  void print() const { cout << str << " : " << frequency << endl; }
};
class Word_Pair /* File: member-class-init-by-mil.h */
{
private:
  Word w1;
  Word w2;

public:
  Word_Pair(const char *s1, const char *s2) : w1(s1, 5), w2(s2) {}
};
