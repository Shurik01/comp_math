#include <iostream>
#include <cmath>
#include <vector>
#include "format"
double func(double x){
    return log(x);
}

int main(){
    std::cout << "Постановка №1" << std::endl;
    int M1 = 1;
    int M2 = 4;
    double x0 = 2;
    double eps = 0.001;
    std::cout << std::endl << "По первой формуле верхний порог для h = " << sqrt(6*eps/M1) << ". Введите желаемое h: ";
    double h1;
    std::cin >> h1;

    double diff1 = (func(x0 + h1) - func(x0 - h1)) / (2 * h1);
    std::cout << "Производная, вычисленная по первой формуле: " << std::format("{:.4}", diff1) << std::endl;
    std::cout << std::endl;
    std::cout << "По второй формуле верхний порог для h = " << pow((30 * eps / M2), 0.25) << ". Введите желаемое h: ";
    double h2;
    std::cin>>h2;
    double diff2 = (func(x0 - 2*h2) - 8 * func(x0 - h2) + 8*func(x0+h2) - func(x0 + 2*h2)) / (12 * h2);
    std::cout <<"Производная, вычисленная по второй формуле: " << std::format("{:.3f}", diff2) << std::endl << std::endl;


    std::cout << "Постановка №2" << std::endl << std::endl;
    std::vector<double> x = {0.2, 0.4, 0.6, 0.8, 1, 1.2};
    std::vector<std::vector<double>> y = {
        {0.2027, 0, 0, 0, 0, 0},
        {0.4228, 0, 0, 0, 0, 0},
        {0.6841, 0, 0, 0, 0, 0},
        {1.0296, 0, 0, 0, 0, 0},
        {1.5574, 0, 0, 0, 0, 0},
        {2.5722, 0, 0, 0, 0, 0}
    };
    double h = 0.2;
    int n = x.size();

    for (int j = 1; j < n; j++) {         
        for (int i = 0; i < n - j; i++) { 
            y[i][j] = y[i + 1][j - 1] - y[i][j - 1];
        }
    }

    double s = 0;
    int d = -1;
    for (int j = 1; j < n - 1; j++){
        d = d * (-1);
        s += d * y[0][j] / (j * h); 
        double delta = std::fabs(y[0][j+1] / ((j + 1) * h));
        std::cout << "m = " << j << std::endl;
        std::cout << "y(x0) = " << s << std::endl;
        std::cout << "delta = " << delta << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

