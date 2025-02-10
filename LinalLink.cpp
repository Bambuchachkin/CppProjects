#include <iostream>
using namespace std;
#include "LL.hpp"
#include "LL.cpp"

int main(){
    cout<<"Введите размеры матрицы: ";
    int a = 0;
    int b = 0;
    cin>>a>>b;
    Matrix m(a,b);
    cout<<"Введите содержимое матрицы:"<<endl;
    // m.def_2();
    m.def();
    
    cout<<endl;
    cout<<"det"<<endl;
    cout<<m.det()<<endl;

    cout<<endl;
    cout<<"multiplay_by_N"<<endl;
    m.multiply_by_N(2);
    m.print();

    cout<<endl;
    cout<<"transpose"<<endl;
    m.transpose();
    m.print();

    cout<<endl;
    cout<<"rank"<<endl;
    cout<<m.rank()<<endl;
}