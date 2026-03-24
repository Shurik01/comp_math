#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double func(vector<double> x){
    return exp(0.8 * pow(( x[0] - 0.7), 2) + 0.8 * pow( (x[1] - 0.6), 2) + 0.1 * pow((x[2] - 0.6), 4) + 4);
}

vector<double> gradF(vector<double> x){
    vector<double> grad(3);
    double factor = func(x);
    grad[0] = 1.6 * (x[0] - 0.7) * factor; 
    grad[1] = 1.6 * (x[1] - 0.6) * factor;
    grad[2] = 0.4 * pow((x[2] - 0.6), 3) * factor; 
    return grad;
}

vector<double> plus(vector<double> a, vector<double> b){
    vector<double> ab(a.size());
    for (int i = 0; i < a.size(); i++){
        ab[i] = a[i] + b[i];
    }
    return ab;
}

vector<double> sub(vector<double> a, vector<double> b){
    vector<double> ab(a.size());
    for (int i = 0; i < a.size(); i++){
        ab[i] = a[i] - b[i];
    }
    return ab;
}

vector<double> mult(vector<double> a, double t){
    vector<double> at(a.size());
    for (int i = 0; i < a.size(); i++){
        at[i] = a[i] * t;
    }
    return at;
}

double scalProd(vector<double> a, vector<double> b){
    double scp = 0;
    for (int i = 0; i < a.size(); i++){
         scp += a[i] * b[i];
    }
    return scp;
}

double length(vector<double> a){
    return sqrt(scalProd(a, a));
}

vector<double> find_ab(vector<double> x, double d){
    double t = 0;
    vector<double> grad = gradF(x);
    vector<double> x_l = sub(x, mult(grad, t - d));
    vector<double> x_c = sub(x, mult(grad, t));
    vector<double> x_h = sub(x, mult(grad, t + d));
    double a = 0;
    double b = 0;
    
    if ( (func(x_l) < func(x_c)) && (func(x_c) > func(x_h)) ){
        cout << "Функция не унимодальна" << endl;
        a = 0;
        b = 0;
    }
    else if ( (func(x_l) > func(x_c)) && (func(x_c) < func(x_h)) ){
        a = t - d;
        b = t + d;
    }
    else {
        double h = 0;
        if ( (func(x_l) > func(x_c)) && (func(x_c) > func(x_h)) ){
            h = d;
        }
        else if ( (func(x_l) < func(x_c)) && (func(x_c) < func(x_h))){
            h = -d;
        }

        double t_prev = t - h;
        vector<double> x_prev = sub(x, mult(grad, t_prev));
        double t_curr = t;
        vector<double> x_curr = sub(x, mult(grad, t_curr));
        double t_next = t + h;
        vector<double> x_next = sub(x, mult(grad, t_next));
        
        while (!((func(x_prev) > func(x_curr)) && (func(x_curr) < func(x_next)))){
            h = 2 * h;
            t_prev = t_curr;
            x_prev = x_curr;
            t_curr = t_next;
            x_curr = x_next;
            t_next = t + h;
            x_next = sub(x, mult(grad, t_next));
        }

        if (h > 0){
            a = t_prev;
            b = t_next;
        }
        else{
            a = t_next;
            b = t_prev;
        }
    }
    vector<double> ab(2);
    ab[0] = a;
    ab[1] = b;
    return ab;
} 

double halfDivision(vector<double> x, vector<double> ab, double eps){
    int k = 0;
    double t0 = ab[0];
    double t4 = ab[1];
    vector<double> grad = gradF(x);
    
    do{
        double t1 = (3 * t0 + t4) / 4;
        vector<double> x1 = sub(x, mult(grad, t1));

        double t2 = (2 * t0 + 2 * t4) / 4;
        vector<double> x2 = sub(x, mult(grad, t2));

        double t3 = (t0 + 3 * t4) / 4;
        vector<double> x3 = sub(x, mult(grad, t3));

        if ((func(x1) > func(x2)) && (func(x2) < func(x3))){
            t0 = t1;
            t4 = t3;
        }
        else if ((func(x1) > func(x2)) && (func(x2) > func(x3))){
            t0 = t2;
        }
        else if ((func(x1) < func(x2)) && (func(x2) < func(x3))){
            t4 = t2;
        }
        k += 1;
    } while(t4 - t0 >= 2 * eps);
    return (t0 + t4) / 2;
}

int main(){
    vector<double> x(3);
    x[0] = 0.4154;
    x[1] = 0.51232;
    x[2] = 0.5422;
    int k = 0;
    cout << "k =" << k << endl;
    cout << "x[0] = " << x[0] << endl;
    cout << "x[1] = " << x[1] << endl;
    cout << "x[2] = " << x[2] << endl;
    
    do{
        vector<double> x_old = x;
        vector<double> ab = find_ab(x_old, 0.1);
        if (ab[0] > 1.0 || ab[1] > 2.0) {
            break;
        }
        double alpha = halfDivision(x_old, ab, 0.0001);
        
        vector<double> x_new = sub(x_old, mult(gradF(x_old), alpha));
        k += 1;
        
        cout << "k = " << k << endl;
        cout << "x[0] = " << x_new[0] << endl;
        cout << "x[1] = " << x_new[1] << endl;
        cout << "x[2] = " << x_new[2] << endl;
        cout << "f(x) = " << func(x_new) << endl;
        
        // Проверка условий остановки
        bool grad_small = length(gradF(x_new)) < 0.0000001;
        bool step_small = length(sub(x_new, x_old)) < 0.0000001;
        
        x = x_new;
        
        if (grad_small && step_small) {
            break;
        }   
    } while(true);
    
    return 0;
}