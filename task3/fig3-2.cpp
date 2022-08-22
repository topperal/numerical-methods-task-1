#include <iostream>
#include <cmath>
using namespace std;

const unsigned int n = 2;

double mA[2][2] = {
    {0, 0},
    {0, 0}
};

double mB[2] = { 0, 0 }; 

double mRes[2] = { 0, 0 };

void mPrint() {                             // вывод матрицы двумерной
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mA[i][j] << " ";
        }
        cout << " = " << mB[i];
        cout << endl;
    }
}
//// НАЧАЛО МЕТОДА ГАУССА
void mDivisionRaw(int nraw, int ncolumn) {          // делили строку на первый элемент
    double start = mA[nraw][ncolumn];
    for (int i = ncolumn; i < n; i++) {
        mA[nraw][i] /= start;
    }
    mB[nraw] /= start;
}

void mSub(int nraw) {                               // вычитали предыдущую строку

    for (int i = nraw + 1; i < n; i++) {
        mDivisionRaw(i, nraw);
        for (int j = 0; j < n; j++) {
            mA[i][j] -= mA[nraw][j];
        }
        mB[i] -= mB[nraw];
    }
}

void mFind(int nrow) {
    double res = mA[0][nrow + 1] * mRes[nrow + 1];
    mRes[nrow] = mB[nrow] - res;
}

// КОНЕЦ МЕТОДА ГАУССА

int main()
{
    setlocale(LC_ALL, "Russian");
 
    double eps = 0.0001;
    double x0 = 1.5; double y0 = 0.5;
    double prevx = 100; double prevy = 100;
    int k = 0;
    while ((fabs(fabs(prevx) - fabs(x0)) > eps) and (fabs(fabs(prevy) - fabs(y0)) > eps)) {
        mA[0][0] = -cos(x0 - 1);
        mA[1][0] = -1;
        mB[0] = -sin(x0 - 1) - y0 + 1.3;
        mA[0][1] = -1;
        mA[1][1] = cos(y0 + 1);
        mB[1] = -x0 + sin(y0 + 1) + 0.8;

        // ГАУСС

        mDivisionRaw(0, 0); // x + a12/a11 y + a13/a11 = b1/a11
        mSub(0);
        mDivisionRaw(1, 1);

        mRes[1] = mB[1];

        mFind(0);

        cout << "(h, g): ";
        for (int i = 0; i < n; i++) {
            cout << mRes[i] << "  ";
        }

        prevx = x0;
        prevy = y0;
        x0 = x0 - mRes[0];
        y0 = y0 - mRes[1];

        cout << endl << "x_" << k << ": " << x0 << endl << "y_" << k << ": " << y0 << endl;
        k++;
        cout << endl;
    }
    // ГАУСС
}
