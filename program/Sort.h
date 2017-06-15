#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Cats.h"
using namespace std;
class Program{
  public:
    int start();
    void merge(int type,const char * fn);
    void search(int type);
    void show(int type);
    void work();
};
