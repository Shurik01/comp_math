#include <iostream>
#include <vector>
#include "format"
using namespace std;

void printVec(vector<double> v){
    for (int i = 0; i < v.size(); i++)
    {
        cout << format("{:.2f}", v[i]) << endl;
    }
    cout << endl;
}

int main(){
    int size = 6;
    vector<double> X = {-1.2, -0.6, 0.5, 1.5, 1.9, 2.6};
    vector<double> Y= {3.38688, -4.35456, 11.71875, 29.53125, 26.00169, 6.88896};
    vector<double> A;
    vector<double> B;
    vector<double> C;
    vector<double> Z;
    Z.push_back(0);
    // квадратичный сплайн
    cout << "Квадратичный сплайн" << endl;
    for (int k = 0; k < size - 1; k++){
        double dx = X[k+1] - X[k];
        double dy = Y[k+1] - Y[k];
        A.push_back (dy / (dx * dx) - Z[k] / dx);
        B.push_back(2 * dy / dx - Z[k]);
        C.push_back( Y[k]);
        Z.push_back(B[k]);
    }
    cout << "Значения X:" << endl;
    printVec(X);

    cout << "Значения Y:" << endl;
    printVec(Y);

    cout << "Значения Z:" << endl;
    printVec(Z);

    cout << "Значения A:" << endl;
    printVec(A);

    cout << "Значения B:" << endl;
    printVec(B);

    cout << "Значения C:" << endl;
    printVec(C);
    
    // кубический сплайн
    cout << endl << endl << "Кубический сплайн" << endl;
    vector <double> D;
    vector <double> W;
    A = {};
    B = {};
    C = {};
    Z = {};
    Z.push_back(-0.01);
    W.push_back(0.02);
    for (int k = 0; k < size-1; k++){
        double dx = X[k+1] - X[k];
        double dy = Y[k+1] - Y[k];
        A.push_back(dy / (dx * dx * dx) - Z[k] / (dx * dx) - W[k] / (2 * dx));
        B.push_back(3 * dy / (dx * dx) - 3 * Z[k] / dx - W[k]);
        C.push_back(3 * dy / dx - 2 * Z[k] - W[k] * dx / 2);
        D.push_back(Y[k]);
        Z.push_back(C[k]);
        W.push_back(2 * B[k]);
    }

    cout << "Значения X:" << endl;
    printVec(X);

    cout << "Значения Y:" << endl;
    printVec(Y);

    cout << "Значения Z:" << endl;
    printVec(Z);

    cout << "Значения W:" << endl;
    printVec(W);

    cout << "Значения A:" << endl;
    printVec(A);

    cout << "Значения B:" << endl;
    printVec(B);

    cout << "Значения C:" << endl;
    printVec(C);

    cout << "Значения D:" << endl;
    printVec(D);

    return 0;
}