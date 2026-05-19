#include <iostream>
#include <cmath>
#include "format"
using namespace std;

double func(double x){
    return 1 / sqrt(3*x*x + 1); 
}

double func2(double x){
    return log2(x*x + 2) / (x+1); 
}
int main(){
    // метод трапеций
    cout << "Метод трапеций:" << endl;

    double a = 0.8;
    double b = 1.8;
    int n = 8;
    double h = (b - a) / n;
    double s = 0;

    for (int k = 0; k < n; k++){
        s += func(a + (k+1) * h);
    }

    s = (h / 2) * (func(a) + func(b) + 2 * s);
    cout << "Интеграл: " << format("{:.3f}", s)<< endl << endl;

    cout << "Метод Симпсона:" << endl;
    n = 2;
    int m = n / 2;
    a = 0.4;
    b = 1.2;
    h = (b-a) / n;
    double s1 = 0;
    for (int k = 1; k <= m; k++){
        s1 += func2(a + (2 * k - 1) * h);
    }

    double s2 = 0;
    for (int k = 1; k < m; k++){
        s2 += func2(a + 2 * k * h);
    }
    s = (h / 3) * (func2(a) + func2(b) + 4 * s1 + 2 * s2);
    cout << "Интеграл: " << format("{:.3f}", s);
    return 0;
}