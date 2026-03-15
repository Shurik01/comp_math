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
    double A[n][n] = {
        {3, 1, 4, 5, 9},
        {4, 3, 5, 9, 5},
        {5, 8, 5, 3, 4},
        {6, 8, 9, 2, 8},
        {6, 8, 2, 8, 9}
    };
    
    double Q[n][n];
    double R[n][n];
    
    cout << "Исходная матрица A:" << endl;
    printMatrix(A);
    
    // Копируем A в Q
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Q[i][j] = A[i][j];
        }
    }

    for (int t = 0; t < 300; t++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                R[i][j] = 0;
            }
        }
        
        // QR-разложение (метод Грама-Шмидта)
        for (int j = 0; j < n; j++) {
            double SQsum = 0;
            for (int m = 0; m < n; m++) {
                SQsum += Q[m][j] * Q[m][j];
            }
            R[j][j] = sqrt(SQsum);
            
            for (int i = 0; i < n; i++) {
                Q[i][j] = Q[i][j] / R[j][j];
            }
            
            for (int k = j + 1; k < n; k++) {
                for (int m = 0; m < n; m++) {
                    R[j][k] += Q[m][j] * Q[m][k];
                }
                
                for (int i = 0; i < n; i++) {
                    Q[i][k] = Q[i][k] - Q[i][j] * R[j][k];
                }
            }
        }
        
        // Вычисляем новую A = R * Q
        double newA[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                newA[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    newA[i][j] += R[i][k] * Q[k][j];
                }
            }
        }
        
        // Копируем newA обратно в Q для следующей итерации
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Q[i][j] = newA[i][j];
            }
        }
        
        // Выводим информацию каждые 50 итераций
        if ((t + 1) % 50 == 0) {
            cout << "\nИтерация " << (t + 1) << ":" << endl;
            cout << "Матрица A(" << (t + 1) << "):" << endl;
            printMatrix(Q);
        }
    }
    
    // Вывод финальной матрицы
    cout << "\nФинальная матрица (после 300 итераций):" << endl;
    printMatrix(Q);
    
    // Собственные значения - диагональные элементы
    cout << "Приближённые собственные значения:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "λ" << (i+1) << " = " << fixed << setprecision(6) << Q[i][i] << endl;
    }
    
    return 0;
}