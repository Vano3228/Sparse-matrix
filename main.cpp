#include <QCoreApplication>
#include <iostream>
#include "class.h"
#include <string>
#include <fstream>
using namespace std;

int main()
{
    int i = 1;
    while (i){
            cout << "Choose number of operation: " << endl
                 << "11 - input from console, sum in console" << endl
                 << "21 - input from console, multi in console" << endl
                 << "31 - input from console, matrix of attainability in console" << endl
                 << "12 - input from file _cxz.txt, sum in file zxc.txt" << endl
                 << "22 - input from file _cxz.txt, multi in file zxc.txt" << endl
                 << "32 - input from file _cxz.txt, matrix of attainability in file zxc.txt" << endl
                 << "0 - exit" << endl;
            cin >> i ; cout << endl;
            if (i==11){               //сумма в консоль
                cout << "mtrx a " << endl;
                mtrxcrs a;
                cout << "mtrx b " << endl;
                mtrxcrs b;
                cout << "mtrx a in crs: " << endl;
                a.myout();
                cout << "mtrx b in crs: " << endl;
                b.myout();
                cout << "sum of mtrx a and b in crs: " << endl;
                mtrxcrs sum(a,b);
                sum.myout();
            }
            else if (i==21){              // умножение в консоль
                cout << "mtrx a " << endl;
                mtrxcrs a;
                cout << "mtrx b " << endl;
                mtrxcrs b;
                cout << "mtrx a in crs: " << endl;
                a.myout();
                cout << "mtrx b in crs: " << endl;
                b.myout();
                cout << "multi of mtrx a and b in crs: " << endl;
                mtrxcrs multi(a , b , 1);
                multi.myout();
            }
            else if (i==31){               // матрица достижимости в консоль
                cout << "mtrx a " << endl;
                mtrxcrs a;
                cout << "mtrx a in crs: " << endl;
                a.myout();
                cout << "attainability matrix of matrix a in crs: " << endl;
                mtrxcrs dost(a , 1);
                dost.myout();
            }
            else if (i==12){                //сумма в файл zxc.txt
                mtrxcrs a("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\acxz.txt");
                mtrxcrs b("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\bcxz.txt");
                mtrxcrs(a,b).mywrite("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\zxc.txt");
            }
            else if (i==22){                 // умножение в файл zxc.txt
                mtrxcrs a("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\acxz.txt");
                mtrxcrs b("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\bcxz.txt");
                mtrxcrs multi(a , b , 1);
                multi.mywrite("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\zxc.txt");
            }
            else if (i==32){                 //матрица достижимости в файл zxc.txt
                mtrxcrs a("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\acxz.txt");
                mtrxcrs dost(a , 1);
                dost.mywrite("C:\\Users\\Vano\\Desktop\\Programmirovanie\\C++\\zxc.txt");
            }
            else if (i==0){                  // выход
                break;
            }
            else{                 // проверка на дурака
                cout << "Input 11,12,13,21,22 or 23 " << endl;
            }
        }
    return 0;
}
