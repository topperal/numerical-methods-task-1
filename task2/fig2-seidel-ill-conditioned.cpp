#include <iostream>
using namespace std;

const unsigned int n = 5;

// плохо обусловленная СЛАУ 3х3

//double mA[3][3] = {
//    {1, -1, -1},
//    {0, 1, -1},
//    {0, 0, 1},
//};
//
//double mA1[3][3] = {
//    {1, -1, -1},
//    {1, 1, -1},
//    {1, 1, 1},
//};
//
//double mB[3] = {-1, -1, 1 };

 //плохо обусловленная СЛАУ 4х4
//double mA[4][4] = {
//    {1, -1, -1, -1},
//    {0, 1, -1, -1},
//    {0, 0, 1, -1},
//    {0,0,0,1}
//};
//
//double mA1[4][4] = {
//    {1, -1, -1,-1},
//    {1, 1, -1,-1},
//    {1, 1, 1,-1},
//    {1,1,1,1}
//};
//
//double mB[4] = { -1, -1, -1, 1 };

// плохо обусловленная СЛАУ 5х5
double mA[n][n] = {
    {1, -1, -1, -1, -1},
    {0, 1, -1, -1,-1},
    {0, 0, 1, -1,-1},
    {0,0,0,1,-1},
    {0,0,0,0,1}
};

double mA1[n][n] = {
    {1, -1, -1,-1, -1},
    {1, 1, -1,-1,-1},
    {1, 1, 1,-1,-1},
    {1,1,1,1,-1},
    {1,1,1,1,1}
};

double mB[n] = { -1, -1, -1, -1, 1 };

double mRes[n] = { 0,0,0,0,0 };

void mPrint() {                             // вывод матрицы двумерной
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mA[i][j] << " ";
        }
        cout << " = " << mB[i];
        cout << endl;
    }
} 
// НАЧАЛО ЗЕЙДЕЛЬ
double mEps[n] = { 0, 0, 0 };
double EPS = 0.000001;

void zeidelResRow(int nraw) {
    double res = mB[nraw]/mA[nraw][nraw];
    for (int i = 0; i < n; i++) {
        if (i != nraw) {
            res -= mA[nraw][i] / mA[nraw][nraw] * mRes[i];
        }
    }
    mEps[nraw] = fabs(mRes[nraw]-res);
    mRes[nraw] = res;
}

double maxEps() {
    double res = mEps[0];
    for (int i = 1; i < n; i++) {
        if (res < mEps[i]) {
            res = mEps[i];
        }
    }
    return res;
}
// КОНЕЦ ЗЕЙДЕЛЯ

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
    cout << "Метод Зейделя" << endl;
    mSum();
    mPrint();
    cout << endl;
    do {
        cout << endl;
        for(int i=0; i<n; i++)
        zeidelResRow(i);
        cout << "X array " << endl;
        for (int i = 0; i < n; i++) {
            cout << mRes[i] << " ";
        }
        cout << endl << "Max e " << maxEps() << endl << "Eps array " << endl;
    } while (maxEps() > EPS);

}

