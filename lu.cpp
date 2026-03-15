#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 5;

void printMatrixA(double B[n][n+1], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(12) << fixed << setprecision(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

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
    double A[n][n+1] = {
        {2, 4, 7, 7, 2, 22},
        {7, 6, 7, 8, 5, 33},
        {4, 4, 2, 1, 1, 12},
        {9, 7, 1, 9, 3, 29},
        {6, 7, 7, 8, 3, 31}
    };
    double L[n][n];
    double U[n][n];
    double Y[n];
    double X[n];
    
    cout << "Исходная матрица:" << endl;
    printMatrixA(A, n);
    
    // Первичное заполнение массивов
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            L[i][j] = 0;
            if (i == j){
                U[i][j] = 1;
            }
            else{
                U[i][j] = 0;  
            }
        }
    }

    //этап 1
    //слой 0
    for (int i = 0; i < n; i++){
        L[i][0] = A[i][0];
    }
    
    for (int j = 1; j < n; j++){
        U[0][j] = A[0][j]/L[0][0];
    }

    //пересчитываем остальные слои
    for (int k = 1; k < n; k++){
        //вычисляем L[i][k]
        for (int i = k; i < n; i++){
            L[i][k] = A[i][k];
            for (int m = 0; m < k-1; m ++){
                L[i][k] = L[i][k] - L[i][m] * U[m][k];
            }
        }
        //вычисляем U[k][j]
        if (k < n){
            for (int j = k+1; j < n; j++){
                U[k][j] = A[k][j];
                for (int m = 0; m < k-1; m++){
                    U[k][j] = U[k][j] - L[k][m] * U[m][j];
                }
                U[k][j] = U[k][j]/L[k][k];
            }
        }
    }

    cout << "Матрица L:" << endl;
    printMatrix(L, n);

    cout << "Матрица U:" << endl;
    printMatrix(U, n);

    //этап 2
    //вычисляем Y
    Y[0] = A[0][n]/L[0][0];
    for (int k = 1; k < n; k++){
        Y[k] = A[k][n];
        for (int m = 0; m < k-1; m++){
            Y[k] = Y[k] - L[k][m] * Y[m];
        }
        Y[k] = Y[k]/L[k][k];
    }

    cout << "Вектор Y:"<< endl;
    for (int k = 0; k < n; k++){
        cout << "Y[" << k + 1 << "] = " << fixed << setprecision(6) << Y[k] << endl;
    }
    cout << endl;

    //этап 3
    //вычисляем X
    X[n] = Y[n];
    for (int k = n-1; k >= 0; k--){
        X[k] = Y[k];
        for (int m = k + 1; m < n; m++){
            X[k] = X[k] - U[k][m] * X[m];
        }
    }

    cout << "Вектор X:" << endl;
    for (int k = 0; k < n; k++){
        cout << "X[" << k + 1 << "] = " << fixed << setprecision(6) << X[k] << endl;
    }

    return 0;
}