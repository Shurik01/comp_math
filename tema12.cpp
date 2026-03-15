#include <math.h>
#include <format>
#include <iostream>

double f(double x){
     return 5*x + pow(4, x) + 8;
 }

 double df(double x){
     return 5 + pow(4, x) * log(4);
 }

double ddf(double x){
     return pow(4, x) * log(4) * log(4);
 } 

//double f(double x){
 //   return x*x*x + 2*x*x - 5*x - 4;
//}

//double df(double x){
 //   return 3*x*x + 4*x - 5;
//}

//double ddf(double x){
 //   return 6*x + 4;
//}

const double EPS = 1e-10;
using namespace std;
int main(){

    //Метод половинного деления
    {
        double a = -10;
        double b = 10;
        double c;
        int count = 0;
        while(abs(b - a) >= 2*EPS){
            count++;
            c = (a+b)/2;
            if (f(a)*f(c) < 0)
                b = c;
            else
                a = c;  
        }

        cout << "Половинного деления\nКорень: "<< (a+b)/2 << " Кол-во итераций: " << count << "\n";
    }

    //Метод хорд
    {
        double a = 0;
        double b = 1;
        double c;
        double c_old = a;
        int count = 0;
        c = ( a*f(b) - b*f(a) ) / ( f(b) - f(a) ); 
        while ( abs(c - c_old) >= EPS ){
        count++;
        if (f(a)*f(c) < 0)
            b = c;
        else
            a = c;
        c_old = c;
        c = ( a*f(b) - b*f(a) ) / ( f(b) - f(a) ); 
        }

        cout << "Хорд\nКорень: "<< c << " Кол-во итераций: " << count << "\n";
    }

    //Метод касательных
    {
        double a = 0;
        double b = 1;
        double d; 
        double d_old = a;
        int count = 0;
        if (f(a)*ddf(a) > 0)
            d = a- f(a) / df(a);
        else
            d = b - f(b) / df(b);
        while ( abs(d - d_old) >= EPS ){
            count++;
            d_old = d;
            if (f(a)*ddf(a) > 0){
                a = d;
                d = a - f(a) / df(a);
            }
            else{
                b = d;
                d = b - f(b) / df(b);
            }
        }
        cout << "Касательных\nКорень: "<< d << " Кол-во итераций: " << count << "\n";
    }

    //Комбинированный метод
    {
        double a = 0;
        double b = 1;
        double c;
        double d;
        int count = 0;
        while(abs(b - a) >= 2*EPS){
            count++;
            c = (a*f(b) - b*f(a)) / ( f(b) - f(a) );
            if (f(a) * ddf(a) >0){
                d = a - f(a) / df(a);
                a = d;
                b = c;
            }
            else{
                d = b - f(b) / df(b);
                b = d;
                a = c;
            }
        }
        cout << "Комбинированный\nКорень: "<< (a+b)/2 << " Кол-во итераций: " << count << "\n";
    }
    return 0;
}