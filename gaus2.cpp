#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int n = 5;

void printMatrix(double B[n][n+1], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(12) << fixed << setprecision(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {   
    // Предопределенная матрица для тестирования
    double B[n][n+1] = {
        {-1.78, 6.71, -0.1, 7.52, -0.36, 6.68},
        {7.59, 1.07, 4.55, 4.48, 0.64, -0.15},
        {9.52, -2.6, -1.09, 1.29, 3.41, -8.76},
        {1.19, 4.6, 6, 9.85, 0.66, -6.15},
        {-0.48, -5.29, 8.75, -3.16, -1.89, 9.32}
    };
    
    double X[n];
    
    cout << "Исходная матрица:" << endl;
    printMatrix(B, n);
    
    // Основной цикл
    for (int k = 0; k < n; k++) {
        
        // Проверка условия B(k,k) == 0
        if (abs(B[k][k]) < 0.00001) {
            int m = k + 1;
            while (m < n) {
                if (abs(B[m][k]) > 0.00001) {
                    break;
                }
                m++;
            }
            
            // Перемена местами строки k и m
            if (m < n) {
                for (int j = 0; j <= n; j++) {
                    double temp = B[k][j];
                    B[k][j] = B[m][j];
                    B[m][j] = temp;
                }
            }
        }
        
        // Применение правила прямоугольника
        for (int i = 0; i < n; i++) {
            for (int j = k + 1; j <= n; j++) {
                if (i!=k){
                    B[i][j] = (B[i][j] * B[k][k] - B[k][j] * B[i][k]) / B[k][k];
                }
            }
        }
        
        // Обнуление элементов ведущего столбца
        for (int i = 0; i < n; i++) {
            if (i!=k){
                B[i][k] = 0;
            }
        }
        
        // Деление ведущей строки на ведущий элемент
        for (int j = n; j >= k; j--) {
            B[k][j] = B[k][j] / B[k][k];
        }
        
        cout << "После итерации " << k + 1 << ":" << endl;
        printMatrix(B, n);
    }
    
    
    
    // Вывод решений
    cout << "Решение системы:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "X[" << k + 1 << "] = " << fixed << setprecision(6) << B[k][n] << endl;
    }
    
    return 0;
}