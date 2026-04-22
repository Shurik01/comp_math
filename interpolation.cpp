// интерполяция многочленами
#include <iostream>
#include <cmath>
#include <iomanip>
#include <format>
using namespace std;

const int n = 6;

void printMatrix(double B[n][n + 1], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(12) << fixed << setprecision(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {  
    cout << "Метод Жордана-Гаусса: " << endl; 
    // Предопределенная матрица для тестирования
    double X[n] = {-1, 1, 3, 5, 7, 9};
    double Y[n] = {3, -7, 5, -3, 4, -9};
    double B[n][n + 1] = {
        {1, -1, 1, -1, 1, -1, 3},
        {1, 1, 1, 1, 1, 1, -7},
        {1, 3, 9, 27, 81, 243, 5},
        {1, 5, 25, 125, 625, 3125, -3},
        {1, 7, 49, 343, 2401, 16807, 4},
        {1, 9, 81, 729, 6561, 59049, -9}
    };
    
    double a[n];
    
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
    cout << "Коэффиценты системы:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "a[" << k + 1 << "] = " << fixed << setprecision(6) << B[k][n] << endl;
        a[k] = B[k][n];
    }
    
    cout << format("Полином имеет вид: {:.2f} + {:.2f}x + {:.2f}x^2 + {:.2f}x^3 + {:.2f}x^4 + {:.2f}x^5", a[0], a[1], a[2], a[3], a[4], a[5]);

    cout << endl << endl << "Метод Лагранжа: " << endl;
    double sum = 0;
    double x = 0;
    cout << "Введите x" << endl;
    cin >> x;
    for (int i = 0; i < n; i++){
        double mult = 1;
        double denom = 1;
        for (int j = 0; j < n; j++){
            if (j != i){
                mult *= (x - X[j]);
                denom *= (X[i] - X[j]);
            }
        }
        sum += Y[i] * (mult / denom);
    }
    cout << "Значение полинома в точке x:" << format("{:.3f}", sum) << endl << endl;
    cout << "Метод Ньютона:" << endl;
    double Y_n[n][n];
    for (int i = 0; i < n; i ++){
        Y_n[i][0] = Y[i];
    }
    
    for (int j = 1; j < n; j++){
        for (int i = 0; i < n-j; i ++){
            Y_n[i][j] = (Y_n[i+1][j-1] - Y_n[i][j-1]) / (X[i+j] - X[i]);
        }    
    }
    double NF = Y_n[0][0];
    double d = 1;
    for (int k = 1; k < n; k++){
        d = d*(x - X[k-1]);
        NF = NF + Y_n[0][k] * d;
    }
    cout << format("Значение полинома в точке x при интерполировании вперед {:.3f}", NF) << endl;

    double NB = Y_n[n-1][0];
    d = 1;
    for (int k = 1; k < n; k++){
        d = d*(x - X[n - k]);
        NB = NB + Y_n[n - 1 - k][k] * d;
    }
    cout << "Значение полинома в точке x при интерполировании назад:" << format("{:.3f}", NB);
    return 0;
}