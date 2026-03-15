#include <iostream>
#include <cmath>
#include <format>

using namespace std;

double func(double* x){
    return exp(0.8 * pow(( x[0] - 0.7), 2) + 0.8 * pow( (x[1] - 0.6), 2) + 0.1 * pow((x[2] - 0.6), 4) + 4);
}

double* gradF(double* x){
    // множитель
    double* grad = new double[3];
    double factor = func(x);
    grad[0] = 1.6 * (x[0] - 0.7) * factor; 
    grad[1] = 1.6 * (x[1] - 0.6) * factor;
    grad[2] = 0.4 * (x[2] - 0.6) * factor;
    return grad;
}

double* plus(double* a, double* b, double* ab, int n){
    for (int i = 0; i < n; i++){
        ab[i] = a[i] + b[i];
    }
    return ab;
}

double* sub(double* a, double* b, int n){
    double* ab = new double[3];
    for (int i = 0; i < n; i++){
        ab[i] = a[i] - b[i];
    }
    return ab;
}

double* mult(double* a, double t, int n){
    double* at = new double[3];
    for (int i = 0; i < n; i++){
        at[i] = a[i] * t;
    }
    return at;
}

double scalProd(double* a, double* b, int n){
    double scp = 0;
    for (int i = 0; i < n; i++){
         scp += a[i] * b[i];
    }
    return scp;
}

double length(double* a, int n){
    return sqrt(scalProd(a, a, n));
}

double* find_ab(double* x, double d){
    double t = 0;
    double* x_l = new double[3];
    double* x_c = new double[3];
    double* x_h = new double[3];
    x_l = sub(x, mult(gradF(x), t, 3), t - d);
    x_c = sub(x, mult(gradF(x), t, 3), t);
    x_h = sub(x, mult(gradF(x), t, 3), t + d);
    double a = 0;
    double b = 0;
    if ( (func(x_l) < func(x_c)) and (func(x_c) > func(x_h)) ){
        cout << "Функция не унимодальна" << endl;
        a = 0;
        b = 0;
    }
    if ( (func(x_l) > func(x_c)) and (func(x_c) < func(x_h)) ){
        a = t - d;
        b = t + d;
    }

    else {
        double h = 0;
        if ( (func(x_l) > func(x_c)) and (func(x_c) > func(x_h)) ){
            h = d;
        }

        if ( (func(x_l) < func(x_c)) and (func(x_c) < func(x_h))){
            h = -d;
        }

        double t_prev = t - h;
        double* x_prev = new double[3];
        x_prev = sub(x, mult(gradF(x), t_prev, 3), 3);
        double t_curr = t;
        double* x_curr = new double[3];
        x_curr = sub(x, mult(gradF(x), t_curr, 3), 3);
        double t_next = t + h;
        double* x_next = new double[3];
        x_next = sub(x, mult(gradF(x), t_next, 3), 3);
        while (!( (func(x_prev) > func(x_curr)) and ( func(x_curr) < func(x_next)))){
            h = 2 * h;
            t_prev = t_curr;
            x_prev = x_curr;
            t_curr = t_next;
            x_curr = x_next;
            t_next = t + h;
            x_next = sub(x, mult(gradF(x), t_next, 3), 3);
        }

        if (h > 0){
            a = t_prev;
            b = t_next;
        }
        else{
            a = t_next;
            b = t_prev;
        }
        delete[] x_prev;
        delete[] x_curr;
        delete[] x_next;
    }
    delete[] x_l;
    delete[] x_c;
    delete[] x_h;
    double* ab = new double[2];
    ab[0] = a;
    ab[1] = b;
    return ab;
} 

double halfDivision(double* x, double* ab, double eps){
    int k = 0;
    double t0 = ab[0];
    double* x0 = new double[3];
    x0 = sub(x, mult(gradF(x), t0, 3), 3);
    double t4 = ab[1];
    double* x4 = new double[3];
    x4 = sub(x, mult(gradF(x), t4, 3), 3);
    do{
        double t1 = (3 * t0 + t4) / 4;
        double* x1 = new double[3];
        x1 = sub(x, mult(gradF(x), t1, 3), 3);

        double t2 = (2 * t0 + 2 * t4) / 4;
        double* x2 = new double[3];
        x2 = sub(x, mult(gradF(x), t2, 3), 3);

        double t3 = (t0 + 3 * t4) / 4;
        double* x3 = new double[3];
        x3 = sub(x, mult(gradF(x), t3, 3), 3);

        if ((func(x1) > func(x2)) and (func(x2) < func(x3))){
            t0 = t1;
            t4 = t3;
        }

        if ((func(x1) > func(x2)) and ( func(x2) > func(x3))){
            t0 = t2;
        }
        if ((func(x1) < func(x2)) and ( func(x2) < func(x3))){
            t4 = t2;
        }
        k += 1;
    } while(t4 - t0 >= 2 * eps);
}

int main(){
    double* x = new double[3];
    return 0;
}
