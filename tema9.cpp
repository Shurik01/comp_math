#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 5;

void printMatrix(double B[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(12) << fixed << setprecision(6) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {   
    // Матрица A из варианта 9
    double A[n][n] = {
        {5, 1, 3, 1, 4},
        {1, 7, 1, 2, 5},
        {3, 1, 8, 5, 3},
        {1, 2, 5, 7, 5},
        {4, 5, 3, 5, 9}
    };
    
    double L[n][n];
    double Y[n][n];
    double AInv[n][n]; 
    
    cout << "матрица A:" << endl;
    printMatrix(A);
    
    // этап 1
    // заполнение матрицы L
    L[0][0] = sqrt(A[0][0]);

    for (int i = 1; i < n; i++) {
        L[i][0] = A[i][0] / L[0][0];
    }
    
    for (int k = 1; k < n; k++) {
        double sqsum = 0;
        for (int m = 0; m < k; m++) {
            sqsum += L[k][m] * L[k][m];
        }
        L[k][k] = sqrt(A[k][k] - sqsum);
    
        if (k < n - 1) {
            for (int i = k + 1; i < n; i++) {
                double pairsum = 0;
                for (int m = 0; m < k; m++) {
                    pairsum += L[i][m] * L[k][m];
                }
                L[i][k] = (A[i][k] - pairsum) / L[k][k];
            }
        }
    }
    
    cout << "Матрица L (нижняя треугольная):" << endl;
    printMatrix(L);
    
    cout << endl;
    
    // этап 2
    // заполнение матрицы Y
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                Y[i][j] = 0;
            }
            else if (j == i) {
                Y[i][j] = 1.0 / L[i][i];
            }
            else { // j < i
                Y[i][j] = 0;
                for (int m = j; m < i; m++) {
                    Y[i][j] = Y[i][j] + L[i][m] * Y[m][j];
                }
                Y[i][j] = Y[i][j] / (-L[i][i]);
            }
        }
    }
    
    cout << "Матрица Y:" << endl;
    printMatrix(Y);
    
    // этап 3
    //Вычисление матрицы, обратной A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AInv[i][j] = 0;
            for (int m = 0; m < n; m++) {
                AInv[i][j] += Y[m][i] * Y[m][j];  // Y[m][i] = Yᵀ[i][m]
            }
        }
    }
    
    cout << "Обратная матрица A:" << endl;
    printMatrix(AInv);
    
    return 0;
}