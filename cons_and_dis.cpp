#include <iostream>
#include "class.h"
#include <string>
#include <fstream>
using namespace std;

mtrxcrs::mtrxcrs(){ // конструктор с заполнением матрицы, но crs делается параллельно,
                    // требует количество ненулевых элементов и все остальные конструкторы с ним работают
    n = 0; // размерность
    k = 0; // количество ненулевых
    l = 0; // для заполнения crs1 и crs2 / количество ненулевых в данный момент
    cout << "Input size of matrix: ";
    cin >> n;
    cout << "Input number of not-zero elements: ";
    cin  >> k;
    n1 = n;
    crs1 = new int [k];
    crs2 = new int [k];
    crs3 = new int [n+1];
    crs3[0] = 0;
    mas = new int* [n];
    for (int i = 0 ; i < n ; i++){
        mas[i] = new int [n];
        for (int j = 0 ; j < n ; j++){
            cout << "Input [" << i << "][" << j << "] ";
            cin >> mas [i][j];
            if (mas [i][j]){
                crs1[l] = 1;
                crs2[l] = j;
                l++;
            }
        }
        crs3[i+1] = l;
    }
    l = 0;
}

mtrxcrs::mtrxcrs(string a){ // ввод из файла, сначала размерность, потом сама матрица
    ifstream in(a);
    if (in){
        k = 0;
        n = 0; // размерность
        l = 0; // для заполнения crs1 и crs2 / количество ненулевых в данный момент
        in >> n;
        n1 = n;
        crs3 = new int [n+1];
        crs3[0] = 0;
        mas = new int* [n];
        for (int i = 0 ; i < n ; i++){
            mas[i] = new int [n];
            for (int j = 0 ; j < n ; j++){
                in >> mas [i][j];
                if (mas [i][j]){
                    k++;
                }
            }
        }
        crs1 = new int [k];
        crs2 = new int [k];
        for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < n ; j++){
                if (mas [i][j]){
                    crs1[l] = 1;
                    crs2[l] = j;
                    l++;
                }
            }
            crs3[i+1] = l;
        }
        l = 0;
    }
    in.close();
}
/*
mtrxcrs::mtrxcrs(){ // конструктор без ввода количества ненулевых и без составления матрицы
                    //(в этом случае неизвестно как делать транспонирование)
    n = 0; // размерность
    k = 0; // количество ненулевых
    l = 0; // для заполнения crs1 и crs2 / количество ненулевых в данный момент
    int c;
    cout << "Input size of matrix: ";
    cin >> n;
    n1 = n;
    int *tmp11, *tmp12 , *tmp21 , *tmp22 , k1 = 0;
    tmp11 = new int[n];
    tmp12 = new int[n];
    tmp21 = new int[k1];
    tmp22 = new int[k1];
    crs3 = new int [n+1];
    crs3[0] = 0;
    for (int i = 0 ; i < n ; i++){
        l = 0;
        cout << "Row " << i << endl
             << "Input colomn(if elements in this row are gone, input -1): ";
        cin >> c;
        while (c != -1){
            tmp11[l] = 1;
            tmp12[l] = c;
            k++;
            l++;
            cin >> c;
        }
        crs1 = new int [k];
        crs2 = new int [k];
        memcpy(crs1 , tmp21 , sizeof(int) * k1);
        memcpy(crs2 , tmp22 , sizeof(int) * k1);
        for (int j = 0 ; j < k-k1 ; j++){
            crs1[k1 + j] = tmp11[j];
            crs2[k1 + j] = tmp12[j];
        }
        k1 = k;
        tmp21 = new int [k1];
        tmp22 = new int [k1];
        memcpy(tmp21 , crs1 , sizeof(int) * k);
        memcpy(tmp22 , crs2 , sizeof(int) * k);
        crs3[i+1] = k;
    }
    delete[] tmp11;
    delete[] tmp21;
    delete[] tmp12;
    delete[] tmp22;
}
*/
mtrxcrs::mtrxcrs(mtrxcrs a , mtrxcrs b){ // сумма в формате crs
    int sa = 0, sb = 0, sums = 0;
    n1 = a.n1;
    crs1 = new int [a.k + b.k];
    crs2 = new int [a.k + b.k];
    crs3 = new int [n1 + 1];
    crs3[0] = 0;
    for (int i = 0 ; i < n1 ; i++){        
        sa = a.crs3[i];
        sb = b.crs3[i];
        while ((sa < a.crs3[i+1]) && (sb < b.crs3[i+1])){
            if ((a.crs2[sa]) < (b.crs2[sb])){
                crs1[sums] = 1;
                crs2[sums] = a.crs2[sa];
                sa++;
            }
            else if ((b.crs2[sb]) < (a.crs2[sa])){
                crs1[sums] = 1;
                crs2[sums] = b.crs2[sb];
                sb++;
            }
            else {
                crs1[sums] = 1;
                crs2[sums] = b.crs2[sb];
                sa++;
                sb++;
            }
            sums++;
        }
        if (sa == (a.crs3[i+1])){
            while (sb < (b.crs3[i+1])){
                crs1[sums] = 1;
                crs2[sums] = b.crs2[sb];
                sb++;
                sums++;
            }
        }
        if (sb == (b.crs3[i+1])){
            while (sa < (a.crs3[i+1])){
                crs1[sums] = 1;
                crs2[sums] = a.crs2[sa];
                sa++;
                sums++;
            }
        }
        crs3[i+1] = sums;
    }
    k = sums;
}

mtrxcrs::mtrxcrs(mtrxcrs a , mtrxcrs t , int d){ // умножение матриц
    int sa = 0, st = 0, k1 = a.k * t.k, multis = 0;
    n1 = t.n1;
    crs1 = new int[k1];
    crs2 = new int[k1];
    crs3 = new int[n1+1];
    crs3[0] = 0;    
    t.l = 0;
    for (int i = 0 ; i < n1 ; i++){ // транпонирует вторую матрицу и делает crs
        for (int j = 0 ; j < n1 ; j++){
            if (t.mas [j][i]){
                t.crs1[t.l] = 1;
                t.crs2[t.l] = j;
                t.l++;
            }
        }
        t.crs3[i+1] = t.l;
    }
    for (int i = 0 ; i < n1  ; i++){
        for (int j = 0 ; j < n1  ; j++){
            sa = a.crs3[i];
            st = t.crs3[j];
            while ((sa < a.crs3[i+1]) && (st < t.crs3[j+1])){
                if ((a.crs2[sa]) == (t.crs2[st])){
                    crs1[multis] = 1;
                    crs2[multis] = j;
                    multis++;
                    break;
                }
                else if (t.crs2[st] < a.crs2[sa]){
                    st++;
                }
                else if (a.crs2[sa] < t.crs2[st]){
                    sa++;
                }

            }
        }
        crs3[i+1] = multis;
    }
    k = multis;
}

mtrxcrs::mtrxcrs(int a){ //единичная матрица размером a*a
    crs1 = new int[a];
    crs2 = new int[a];
    crs3 = new int[a+1];
    for (int i = 0 ; i < a ; i++){
        crs1[i] = 1;
        crs2[i] = i;
        crs3[i] = i;
    }
    crs3[a] = a;
    k = a;
    n1 = a;
}

mtrxcrs:: mtrxcrs(mtrxcrs a , int b){ // матрица достижимости
    mtrxcrs final = mtrxcrs(a, mtrxcrs(a.n1)), tmp= mtrxcrs(a , 'n');
    for (int i = 0 ; i < a.n1 - 1 ; i++){
        tmp = mtrxcrs(tmp , a , 1);
        final = mtrxcrs(final , tmp);        
    }
    crs1 = final.crs1;
    crs2 = final.crs2;
    crs3 = final.crs3;
    n1 = a.n1;
    k = final.k;
}

mtrxcrs::mtrxcrs(mtrxcrs a , char b){ //создание копии матрицы, но в другом месте памяти (для tmp в матрице достижимости)
    k = a.k;
    n1 = a.n1;
    crs1 = new int [k];
    crs2 = new int [k];
    crs3 = new int [n1 + 1];
    memcpy(crs1 , a.crs1 , sizeof(int) * k);
    memcpy(crs2 , a.crs2 , sizeof(int) * k);
    memcpy(crs3 , a.crs3 , sizeof(int) * n1);
}
