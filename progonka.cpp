#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int n = 5;

int main() {
    double l[n] = {0, 2, 4, 2, 9};
    double c[n] = {3, 9, 4, 7, 3};
    double r[n] = {2, 3, 2, 7, 0};
    double f[n] = {5, 14, 10, 16, 12};
    
    double p[n] = {0};
    double q[n] = {0};
    double x[n] = {0};

    // Заполнение и вывод векторов
    cout << "Вектор l (поддиагональ):" << endl;
    for (int k = 0; k < n; k++) {
        cout << "l[" << k + 1 << "] = " << fixed << setprecision(6) << l[k] << endl;
    }
    cout << endl;

    cout << "Вектор c (главная диагональ):" << endl;
    for (int k = 0; k < n; k++) {
        cout << "c[" << k + 1 << "] = " << fixed << setprecision(6) << c[k] << endl;
    }
    cout << endl;

    cout << "Вектор r (наддиагональ):" << endl;
    for (int k = 0; k < n; k++) {
        cout << "r[" << k + 1 << "] = " << fixed << setprecision(6) << r[k] << endl;
    }
    cout << endl;

    cout << "Вектор f (правая часть):" << endl;
    for (int k = 0; k < n; k++) {
        cout << "f[" << k + 1 << "] = " << fixed << setprecision(6) << f[k] << endl;
    }
    cout << endl;

    // Вычисление и вывод p и q
    p[0] = f[0] / c[0];
    q[0] = r[0] / c[0];
    
    cout << "Прямой ход (прогоночные коэффициенты):" << endl;
    cout << "p[1] = " << fixed << setprecision(6) << p[0] << endl;
    cout << "q[1] = " << fixed << setprecision(6) << q[0] << endl;
    
    for (int k = 1; k < n; k++) {
        p[k] = (f[k] - l[k] * p[k-1]) / (c[k] - l[k] * q[k-1]);
        q[k] = r[k] / (c[k] - l[k] * q[k-1]);
        cout << "p[" << k + 1 << "] = " << fixed << setprecision(6) << p[k] << endl;
        cout << "q[" << k + 1 << "] = " << fixed << setprecision(6) << q[k] << endl;
    }
    cout << endl;

    // Вычисление и вывод x
    x[n-1] = p[n-1];
    
    for (int k = n-2; k >= 0; k--) {
        x[k] = p[k] - q[k] * x[k+1];
    }

    cout << "Решение системы:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "x[" << k + 1 << "] = " << fixed << setprecision(6) << x[k] << endl;
    }

    return 0;
}