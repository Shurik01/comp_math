#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 5;


void printMatrix(double B[n][n], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(12) << fixed << setprecision(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {   
    double A[n][n] = {
        {31, 1, 3, 5, 2},
        {1, 34, 3, 3, 3},
        {2, 4, 23, 1, 5},
        {1, 2, 5, 22, 3},
        {3, 2, 1, 1, 48}
    };
    double C[n] = {54, 87, 86, 67, 60};
    double X[n];
    double XX[n];

    
    cout << "Исходная матрица:" << endl;
    printMatrix(A, n);

    cout << "Вектор C:" << endl;
    for (int k = 0; k < n; k++){
        cout << "C[" << k + 1 << "] = " << fixed << setprecision(6) << C[k] << endl;
    }

    double e = 0.000001;
    int how_many = 0;
    for (int i = 0; i < n; i++){
        X[i] = 0;
    }

    while (how_many !=  n){
        for(int i = 0; i < n; i++){
            XX[i] = C[i];
            for (int j = 0; j < n; j++){
                if (j != i){
                    XX[i] = XX[i] - A[i][j] * X[j];
                }
            }
            XX[i] = XX[i] / A[i][i];
        }
        how_many = 0;
        for (int i = 0; i < n; i++){
            if (abs(X[i] - XX[i]) < e){
                how_many = how_many + 1;
            }
            X[i] = XX[i];
        }
    }

    //Вывод вектора X
    cout << "Вектор X:" << endl;
    for (int k = 0; k < n; k++){
        cout << "X[" << k + 1 << "] = " << fixed << setprecision(6) << X[k] << endl;
    }
    //XX
    cout << "Вектор XX:" << endl;
    for (int k = 0; k < n; k++){
        cout << "XX[" << k + 1 << "] = " << fixed << setprecision(6) << XX[k] << endl;
    }


    return 0;
}