#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 5;


void printMatrix(double B[n][n], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(12) << fixed << setprecision(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {   
    double A[n][n] = {
        {4, 3, 1, 1, 1},
        {3, 6, 1, 1, 3},
        {1, 1, 6, 2, 5},
        {1, 1, 2, 9, 3},
        {1, 3, 5, 3, 8}
    };
    double L[n][n];
    double U[n][n];
    double B[n] = {16, 23, 30, 30, 36};
    double Y[n];
    double X[n];
    double sqSum;
    double pairSum;
    
    cout << "Исходная матрица:" << endl;
    printMatrix(A, n);
    
    // Этап №1
    
    //Заполнение матрицы L
    L[0][0] = sqrt(A[0][0]);
    for (int i = 0; i < n; i++) 
    {
        L[i][0] = A[i][0] / L[0][0];
    }

    for (int k = 1; k < n; k++)
    {
        sqSum = 0;
        for (int m = 0; m < k; m++)
        {
            sqSum = sqSum + L[k][m] * L[k][m];
        }
        L[k][k] = sqrt(A[k][k] - sqSum);
        if (k < n - 1)
        {
            for (int i = k + 1; i < n; i++)
            {
                pairSum = 0;
                for (int m = 0; m < k; m++)
                {
                    pairSum = pairSum + L[i][m] * L[k][m];
                }
                L[i][k] = (A[i][k] - pairSum) / L[k][k];
            }
        }
    }
    
    //заполнение матрицы U
    for (int i = 0; i< n; i++){
        for (int j = 0; j < n; j++){
            U[i][j] = L[j][i];
        }
    }

    //вывод матрицы L
    cout << "Матрица L:" << endl;
    printMatrix(L, n);
    //вывод матрицы U
    cout << "Матрица U:" << endl;
    printMatrix(U, n);

    //Этап №2

    //Выисление Y
    Y[0] = B[0] / L[0][0];
    for (int i = 1; i < n; i++){
        Y[i] = B[i];
        for(int m = 0; m < i; m++){
            Y[i] = Y[i] - L[i][m] * Y[m];
        }
        Y[i] = Y[i] / L[i][i];
    }

    //Вывод вектора Y
    cout << "Вектор Y:" << endl;
    for (int k = 0; k < n; k++){
        cout << "Y[" << k + 1 << "] = " << fixed << setprecision(6) << Y[k] << endl;
    }

    //Этап №3

    //Вычисление X
    X[n-1] = Y[n-1] / U[n-1][n-1];
    
    for (int i = n-2; i >= 0; i--){
        X[i] = Y[i];
        for (int m = i + 1; m < n; m++){
            X[i] = X[i] - U[i][m] * X[m];
        }
        X[i] = X[i] / U[i][i];
    }

    //Вывод вектора X
    cout << "Вектор X:" << endl;
    for (int k = 0; k < n; k++){
        cout << "X[" << k + 1 << "] = " << fixed << setprecision(6) << X[k] << endl;
    }

    return 0;
}