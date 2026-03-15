#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int n = 4;  // Размер исходной матрицы

void printMatrix(double B[n][2*n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2*n; j++) {
            cout << setw(12) << fixed << setprecision(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    double B[n][2*n] = {
        {3, 1, 4, 5, 1, 0, 0, 0},
        {4, 3, 5, 9, 0, 1, 0, 0},
        {5, 8, 5, 3, 0, 0, 1, 0},
        {6, 8, 9, 2, 0, 0, 0, 1}
    };

    cout << "Исходная расширенная матрица [A|E]:" << endl;
    printMatrix(B);

    for (int k = 0; k < n; k++) {
        if (abs(B[k][k]) < 1e-10) {
            for (int i = k + 1; i < n; i++) {
                if (abs(B[i][k]) > 1e-10) {
                    for (int j = 0; j < 2*n; j++) {
                        B[k][j] = B[k][j] + B[i][j];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = k + 1; j < 2*n; j++) {
                if (i != k) {
                    B[i][j] = (B[i][j] * B[k][k] - B[k][j] * B[i][k]) / B[k][k];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (i != k) {
                B[i][k] = 0;
            }
        }

        for (int j = 2*n - 1; j >= k; j--) {
            B[k][j] = B[k][j] / B[k][k];
        }

        cout << "После итерации " << k+1 << ":" << endl;
        printMatrix(B);
    }

    cout << "Обратная матрица A^(-1):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2*n; j++) {
            cout << setw(12) << fixed << setprecision(6) << B[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}