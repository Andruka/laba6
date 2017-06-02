#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
using namespace std;
class Generator{
    class Cat{
      public:
        string c_name;
	string c_breed;
        char c_gender;
        int c_age;
        Cat(string n,string b,char s,int a);
        void print(ofstream & fout);
    };
    int fsize,msize,bsize;
    vector<string>vF,vM,vB;
    string name;
    string breed;
    char gender;
    int age;
  public:
    bool check(ifstream & fin,vector<string> & v);
    bool work(int quantity,int max_age);
};
