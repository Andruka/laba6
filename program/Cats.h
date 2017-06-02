#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
class Program;
class Cat{
    string name;
    string breed;
    char gender;
    int age;
  public:
    Cat();
    Cat(string n,string b,char g,int a);
    Cat& operator = (const Cat& cat);
    friend ostream & operator << (ostream & stream, const Cat& cat);
    friend istream & operator >> (istream & stream, Cat& cat);
    friend Program;
};
class Program{
    string t_name;
    string t_breed;
    char t_gender;
    int t_age;    
  public:
    int start();
    int compare(Cat cat1,Cat cat2,int type);
    void sort(int type);
    void work();
};

