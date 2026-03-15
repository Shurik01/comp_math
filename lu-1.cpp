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
        {3, 1, 4, 5, 9},
        {4, 3, 5, 9, 5},
        {5, 8, 5, 3, 4},
        {6, 8, 9, 2, 8},
        {6, 8, 2, 8, 9}
    };
    double L[n][n];
    double U[n][n];
    double LInv[n][n];
    double UInv[n][n];
    double AInv[n][n];
    
    cout << "Исходная матрица:" << endl;
    printMatrix(A, n);
    
    // Первичное заполнение матриц L и U
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
            for (int m = 0; m < k; m ++){
                L[i][k] = L[i][k] - L[i][m] * U[m][k];
            }
        }
        //вычисляем U[k][j]
        if (k < n-1){
            for (int j = k+1; j < n; j++){
                U[k][j] = A[k][j];
                for (int m = 0; m < k; m++){
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

    //вычисляем матрицу, обратную L
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j > i){
                LInv[i][j] = 0;
            }
            if (j == i){
                LInv[i][j] = 1 / L[i][i];
            }
            if (j < i){
                LInv[i][j] = 0;
                for (int m = j; m < i; m++){
                    LInv[i][j] = LInv[i][j] - L[i][m] * LInv[m][j];
                }
                LInv[i][j] = LInv[i][j] / L[i][i];
            }
        }
    }

    //вычисляем матрицу, обратную U
    for (int i = n - 1; i >= 0; i--){
        for (int j = n - 1; j >= 0; j--){
            if (j < i){
                UInv[i][j] = 0;
            }
            if (j == i){
                UInv[i][j] = 1;
            }
            if (j > i){
                UInv[i][j] = 0;
                for (int m = i + 1; m <= j; m++){
                    UInv[i][j] = UInv[i][j] - U[i][m] * UInv[m][j];
                }
            }
        }
    }
    cout << "Обратная матрица L:" << endl;
    printMatrix(LInv, n);

    cout << "Обратная матрица U:" << endl;
    printMatrix(UInv, n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j ++){
            AInv[i][j] = 0;
            for (int m = 0; m < n; m++){
                AInv[i][j] = AInv[i][j] + UInv[i][m] * LInv[m][j];
            }
        }
    }

    cout << "Обратная матрица A:" << endl;
    printMatrix(AInv, n);
    return 0;
}