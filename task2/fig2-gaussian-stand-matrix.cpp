#include <iostream>
using namespace std;

const unsigned int n = 3;

double mA[n][n] = {
    { 15, 1, 1 },
    { 1, 17, 1},
    { 1, 1, 19 }
};

double mB[n] = { 17, 19, 21 };


double mRes[n] = { 0,0,0};

void mPrint() {                             // вывод матрицы двумерной
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mA[i][j] << " ";
        }
        cout << " = " << mB[i];
        cout << endl;
    }
}
// НАЧАЛО МЕТОДА ГАУССА
void mDivisionRaw(int nraw, int ncolumn) {          // делили строку на первый элемент
    double start = mA[nraw][ncolumn];
    for (int i = ncolumn; i < n; i++) {
        mA[nraw][i] /= start;
    }
    mB[nraw] /= start;
}

void mSub(int nraw) {                               // вычитали предыдущую строку
    
    for (int i = nraw+1; i < n; i++) {
        mDivisionRaw(i, nraw);
        for (int j = 0; j < n; j++) {
            mA[i][j] -= mA[nraw][j];
        }
        mB[i] -= mB[nraw];
    }
    mPrint();
    cout << endl;
}
    
void mFind(int nraw) {                          // находили решения
    double res = 0;
    for (int i = nraw; i < n; i++) {
        res += mA[nraw][i] * mRes[i];
    }
    mRes[nraw] = mB[nraw] - res;
}
// КОНЕЦ МЕТОДА ГАУССА

void mSum() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mA[i][j] += mA1[i][j] * 0.001 * 13;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    mSum();

    // ГАУСС
    cout << "Метод Гаусса" << endl;
    mPrint();
    cout << endl;
    mDivisionRaw(0, 0); // x + a12/a11 y + a13/a11 = b1/a11

    for (int i = 1; i < n; i++) {
        mSub(i-1);
        for (int j = i; j < n; j++) {
            mDivisionRaw(j, i);
        }
    }
    
    mRes[n-1] = mB[n-1];
    mDivisionRaw(2, 2);
    for (int i = n - 2; i >= 0; i--) {
        mFind(i);
    }
    cout << "X: " << endl;
    for (int i = 0; i < n; i++) {
        cout << mRes[i] << " ";
    }
    // ГАУСС
}

