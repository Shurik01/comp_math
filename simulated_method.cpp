#include <iostream>
#include "vector"
#include "random"
#include "cmath"
using namespace std;
// метод имитации отжига
double f(vector<double> x){
    return log(0.8 * pow(x[0] - 0.8, 4) + 0.4*pow(x[1] - 0.4, 2) + 0.4 * pow(x[2] - 0.1, 2) + 5);
}

int main(){
    random_device rd;
    std::mt19937 gen(rd());
    uniform_real_distribution<> distr(0, 1);
    vector<double> x_old(3);
    vector<double> x_new(3);
    x_old[0] = 0.5;
    x_old[1] = 0.4;
    x_old[2] = 0.3;
    double t = 1000;
    double t_min = 0.001;
    double max_step = 0.8;
    size_t k = 0;
    string decision = "Начальная точка";
    cout << "k = " << k << "   t = " << t << "   x[0] = " << x_old[0] << "   x[1] = " << x_old[1]<< "   x[2] = " << x_old[2] << "   f(x) = " << f(x_old) << "   df(x) = 0   p = 0   Начальная точка" << endl;
    while(t > t_min){
        k+=1;
        t *= 0.95;
        double a = max_step * (distr(gen) - 0.5);
        double b = max_step * (distr(gen) - 0.5);
        double c = max_step * (distr(gen) - 0.5);
        x_new[0] = x_old[0] + a;
        x_new[1] = x_old[1] + b;
        x_new[2] = x_old[2] + c;
        double df = f(x_new) - f(x_old);
        double p = 0;
        if (df <= 0){
            x_old[0] = x_new[0];
            x_old[1] = x_new[1];
            x_old[2] = x_new[2];
            decision = "перешли в новую точку с уменьшением f(x)";
        }
        else{
            if (distr(gen) < exp(-df/t)){
                x_old[0] = x_new[0];
                x_old[1] = x_new[1];
                x_old[2] = x_new[2];
                decision = "перешли в новую точку с увеличением f(x)";
            }
            else decision = "остались в старой точке";
            p = exp(-df / t);
        }
        cout << "k = " << k << "   t = " << t << "   x[0] = " << x_old[0] << "   x[1] = " << x_old[1]<< "   x[2] = " << x_old[2] << "   f(x) = " << f(x_old) << "   df(x) = " << df <<"   p = "<<p <<"   " << decision << endl;
    }
    return 0;
}