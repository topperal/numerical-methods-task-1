#include <iostream>
using namespace std;
//МЕТОД НАИСКОРЕЙШЕГО ГРАДИЕНТНОГО СПУСКА (МНГС)
double eps = pow(10, -6);//погрешность
int countX = 0;
const unsigned int n = 3;//размерность матрицы


//f(x, y, z) = 2x^2+ (3 + 0, 1·N)y^2+ (4 + 0, 1·N)z^2+ xy−yz + xz + x−2y + 3z + N, N = 13
double mA[n][n] = {
    { 4, 1, 1},
    { 1, 8.6, -1},
    { 1, -1, 10.6 }
};

double mB[n] = { 1, -2, 3 };

double currX[n] = { 1, 0, 0 };//вектор текущего решения

double calcX[n] = { 0, 0, 0 };//вектор вычисленного решения

double mQ[n] = { 0, 0, 0 };

double m = 0;

void func(double mA[n][n], double mB[n], double currX[n]) {
    double f = 0.5 * (mA[0][0] * currX[0] * currX[0]  + mA[1][1] * currX[1] * currX[1] + mA[2][2] * currX[2] * currX[2] + 
        (mA[0][1] + mA[1][0])* currX[0] * currX[1] + (mA[0][2] + mA[2][0]) * currX[0] * currX[2] + (-mA[1][2] - mA[2][1]) * currX[1] * currX[2]) 
        + currX[0] * mB[0] - currX[1] * mB[1] + currX[2] * mB[2] + 13;
    cout << "f(x_k) = " << f << endl;
}

//вычиялем q_n=A*x_n+b
void calculateQ(double mA[n][n], double currX[n], double mB[n]) {

    double summ = 0;
    for (int i = 0; i < n; i++) {
        summ = 0;
        for (int j = 0; j < n; j++) {
            summ += mA[i][j] * currX[j];
        }
       
        mQ[i] = summ+mB[i];
        cout << "q[" << i << "] = " << mQ[i] << endl;
    }
}
//вычисляем m_n = - q_n^T*q_n/(q_n^T*Aq_n)
void calculateM(double mA[n][n], double mQ[n]) {
    //вычисляем числитель: q_n^T*q_n - получается число
    double numerator = 0;
    for (int i = 0; i < n; i++) {
          numerator += mQ[i] * mQ[i];
    }
    cout << "Result q^T*q (numerator): " << numerator << endl;

    double mM[n] = { 0, 0, 0 };//вспомогательная матрица для записи произведения Aq_n
    double summ = 0;
    for (int i = 0; i < n; i++) {
        summ = 0;
        for (int j = 0; j < n; j++) {
            summ += mA[i][j] * mQ[j];
        }
        mM[i] = summ;
        cout << "Result A*q[" << i << "] = " << mM[i] << endl;
    }
    //вычисляем знаменатель q_n^T*Aq_n - получаем число
    double denominator = 0;
    for (int i = 0; i < n; i++) {
        denominator += mM[i] * mQ[i];       
    }
    cout << "Result q^T*Aq (denominator): " << denominator << endl;

    m = - numerator / denominator;//собираем конечное значение для мью
    cout << "Result m: " << m << endl;
}
//вычисляем x_n = x_n-1 + m_n*e_n
void calculateX(double currX[n], double m, double mQ[n]) {
    countX++;
    for (int i = 0; i < n; i++) {
        calcX[i] = currX[i] + m * mQ[i];
        cout << "x_" << countX << "[" << i << "] = " << calcX[i] << endl;
    }
}

int main()
{
    cout.precision(10);
    func(mA, mB, currX);
    cout << endl; 
    bool exit = false;
    while (exit == false) {
        calculateQ(mA, currX, mB);
        calculateM(mA, mQ);
        calculateX(currX, m, mQ);
        double h = sqrt((currX[0] - calcX[0]) * (currX[0] - calcX[0]) + (currX[1] - calcX[1]) * (currX[1] - calcX[1]) +
            (currX[2] - calcX[2]) * (currX[2] - calcX[2]));
        cout << h << endl;
        //sqrt(summ(||currx-calcx||))
        if(sqrt((currX[0]-calcX[0])* (currX[0] - calcX[0]) + (currX[1] - calcX[1]) * (currX[1] - calcX[1]) + 
             (currX[2] - calcX[2]) * (currX[2] - calcX[2])) <= eps) {
            exit = true;
        }
        for (int i = 0; i < n; i++) {//перезаписываем вычисленное решение в текущий вектор решений
            currX[i] = calcX[i];
        }
        func(mA, mB, currX);
        cout << endl; 
    } 
}
