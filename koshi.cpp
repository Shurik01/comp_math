#include <iostream>
#include "cmath"
#include <vector>
using namespace std;
// уравнение Коши
double f(double x, double y){
    return cos(2*x) * cos(2*y) * cos(2*y);
}
// y0 = 0.500
// метод эйлера
void euler(double x0, double y0, double h, size_t k){
    vector<double> xx;
    vector<double> yy;
    xx.push_back(x0);
    yy.push_back(y0);
    for (size_t n = 0; n < k; n++){
        cout << "n=" << n << endl;
        cout << "xx[" << n << "] = " << xx[n] << endl;
        cout << "yy[" << n << "] = " << yy[n] << endl;
        if(n < k){
            xx.push_back(xx[n] + h);
            yy.push_back(yy[n] + h * f(xx[n], yy[n]));
        }
    }
}

// модифицированный метод Эйлера
void eulerMod(double x0, double y0, double h, size_t k){
    vector<double> xx;
    vector<double> yy;
    xx.push_back(x0);
    yy.push_back(y0);
    for (size_t n = 0; n < k; n++){
        cout << "n = " << n << endl;
        cout << "xx[" << n << "] = " << xx[n] << endl;
        cout << "yy[" << n << "] = "<< yy[n] << endl;
        if (n < k){
            xx.push_back(xx[n] + h);
            yy.push_back(yy[n] + h * f(xx[n] + h/2,
                 yy[n] + (h/2) * f(xx[n], yy[n])));
        }
    }
}

// метод Рунге-Кутта
void rungeKutt(double x0, double y0, double h, size_t k){
    vector <double> xx;
    vector <double> yy;
    xx.push_back(x0);
    yy.push_back(y0);
    for (size_t n = 0; n < k; n++){
        cout << "n = " << n << endl;
        cout << "xx[" << n << "] = " << xx[n] << endl;
        cout << "yy[" << n << "] = "<< yy[n] << endl;
        if (n < k){
            xx.push_back(xx[n] + h);
            double a = h * f(xx[n], yy[n]);
            double b = h * f(xx[n] + h/2, yy[n] + a/2);
            double c = h * f(xx[n] + h/2, yy[n] + b/2);
            double d = h * f(xx[n] + h, yy[n] + c);
            yy.push_back(yy[n] + (a + 2 * b + 2 * c + d) / 6);
        }
    }
}

void adams(double x0, double y0, double h, size_t k){
    vector <double> xx;
    vector <double> yy;
    xx.push_back(x0);
    yy.push_back(y0);
    cout << "При m = 1" << endl;
    // m = 1
    for (size_t n = 0; n < k; n++){
        cout << "n = " << n << endl;
        cout << "xx[" << n << "] = " << xx[n] << endl;
        cout << "yy[" << n << "] = "<< yy[n] << endl;
        if (n < 1){
            xx.push_back(xx[n] + h);
            double a = h * f(xx[n], yy[n]);
            double b = h * f(xx[n] + h/2, yy[n] + a/2);
            double c = h * f(xx[n] + h/2, yy[n] + b/2);
            double d = h * f(xx[n] + h, yy[n] + c);
            yy.push_back(yy[n] + (a + 2 * b + 2 * c + d) / 6);
        }
        else{
            if (n < k){
                xx.push_back(xx[n] + h);
                double aa = f(xx[n], yy[n]);
                double bb = f(xx[n-1], yy[n-1]);
                yy.push_back(yy[n] + (h/2) * (3 * aa - bb));
            }
        }
    }
    cout << endl << endl;
    cout << "При m = 2";
    // m = 2
    xx.clear();
    yy.clear();
    xx.push_back(x0);
    yy.push_back(y0);
    for (size_t n = 0; n < k; n++){
        cout << "n = " << n << endl;
        cout << "xx[" << n << "] = " << xx[n] << endl;
        cout << "yy[" << n << "] = "<< yy[n] << endl;
        if (n < 2){
            xx.push_back(xx[n] + h);
            double a = h * f(xx[n], yy[n]);
            double b = h * f(xx[n] + h/2, yy[n] + a/2);
            double c = h * f(xx[n] + h/2, yy[n] + b/2);
            double d = h * f(xx[n] + h, yy[n] + c);
            yy.push_back(yy[n] + (a + 2 * b + 2 * c + d) / 6);
        }   
        else{
            if (n < k){
                xx.push_back(xx[n] + h);
                double aa = f(xx[n], yy[n]);
                double bb = f(xx[n-1], yy[n-1]);
                double cc = f(xx[n-2], yy[n-2]);
                yy.push_back(yy[n] + (h/12) * (23 * aa - 16 * bb + 5 * cc));
            }
        }
    }
    cout << endl << endl;
    cout << "При m = 3" << endl;
    // m = 3
    xx.clear();
    yy.clear();
    xx.push_back(x0);
    yy.push_back(y0);
    for (size_t n = 0; n < k; n++){
        cout << "n = " << n << endl;
        cout << "xx[" << n << "] = " << xx[n] << endl;
        cout << "yy[" << n << "] = "<< yy[n] << endl;
        if (n < 3){
            xx.push_back(xx[n] + h);
            double a = h * f(xx[n], yy[n]);
            double b = h * f(xx[n] + h/2, yy[n] + a/2);
            double c = h * f(xx[n] + h/2, yy[n] + b/2);
            double d = h * f(xx[n] + h, yy[n] + c);
            yy.push_back(yy[n] + (a + 2 * b + 2 * c + d) / 6);
        }   
        else{
            if (n < k){
                xx.push_back(xx[n] + h);
                double aa = f(xx[n], yy[n]);
                double bb = f(xx[n-1], yy[n-1]);
                double cc = f(xx[n-2], yy[n-2]);
                double dd = f(xx[n-3], yy[n-3]);
                yy.push_back(yy[n] + (h/24) * (55 * aa - 59 * bb + 37 * cc - 9 * dd));
            }
        }  
    }
}


int main(){
    double x0 = 0;
    double y0 = 0.5;
    double h = 0.75;
    double n = 11;
    cout << "Метод Эйлера:" << endl;
    euler(x0, y0, h, n);
    cout << endl << endl;
    cout << "Модифицированный метод Эйлера: " << endl;
    eulerMod(x0, y0, h, n);
    cout << endl << endl;
    cout << "Метод Рунге-Кутта:" << endl;
    rungeKutt(x0, y0, h, n);
    cout << endl << endl;
    cout << "Метод Адамса(трех порядков): " << endl;
    adams(x0, y0, h, n);
    return 0;
}