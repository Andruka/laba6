#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
class Cat{
    char name[64];
    char breed[64];
    char age[2];
    char gender;
  public:
    Cat();
    Cat(char* n,char* b,char* a,char g);
    void print();
    Cat& operator = (const Cat& cat);
    friend ostream & operator << (ostream & stream, const Cat& cat);
    friend istream & operator >> (istream & stream, Cat& cat);
    friend int compare_for_merge(Cat cat1,Cat cat2,int type);
    friend int compare_for_search(Cat cat,char * buf,int type);
};


