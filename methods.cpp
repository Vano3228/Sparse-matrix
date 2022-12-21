#include <iostream>
#include "class.h"
#include <string>
#include <fstream>
using namespace std;

void mtrxcrs::myout(){ //вывод в консоли
    cout << "crs1 = ";
    for (int i = 0 ; i < k ; i++){
        cout << crs1[i] << ' ';
    }
    cout << "crs2 = ";
    for (int i = 0 ; i < k ; i++){
        cout << crs2[i] << ' ';
    }
    cout << "crs3 = ";
    for (int i = 0 ; i < n1+1 ; i++){
        cout << crs3[i] << ',';
    }
    cout << '\n' << '\n';
}
void mtrxcrs::mywrite(string file) { // вывод в файл
    ofstream out;
    out.open(file);
    if (out.is_open())
    {
        out << "crs1 = ";
        for (int i = 0 ; i < k ; i++){
            out << crs1[i] << ' ';
        }
        out << endl<< "crs2 = ";
        for (int i = 0 ; i < k ; i++){
            out << crs2[i] << ' ' ;
        }
        out << endl << "crs3 = ";
        for (int i = 0 ; i < n1+1 ; i++){
            out << crs3[i] << ',' ;
        }
        out << '\n' << '\n';
    }
    out.close();
}
