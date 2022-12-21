#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class mtrxcrs{
    int **mas, *crs1 , *crs2, *crs3;
    int l,n1,n,k;
public:    
    mtrxcrs();
    mtrxcrs(int a);
    mtrxcrs(string a);
    mtrxcrs(mtrxcrs a , char b);
    mtrxcrs(mtrxcrs a , int b);
    mtrxcrs(mtrxcrs a , mtrxcrs b);
    mtrxcrs(mtrxcrs a , mtrxcrs t , int b);
    void mywrite(string a);
    void myout();
};
#endif // CLASS_H
