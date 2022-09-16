#include <iostream>
using namespace std;
//МЕТОД НАИСКОРЕЙШЕГО ПОКООРДИНАТНОГО СПУСКА (МНПС)
double eps = pow(10, -6); //погрешность
int countX = 0;
const unsigned int n = 3; //размерность матрицы

double mA[n][n] = {
    { 4, 1, 1},
    { 1, 8.6, -1},
    { 1, -1, 10.6 }
};

double mB[n] = { 1, -2, 3 };

double currX[n] = { 0, 0, 0 };//вектор текущего решения

double calcX[n] = { 0, 0, 0 };//вектор вычисленного решения

double mQ[n] = { 0, 0, 0 };

double calcF[n] = { 0, 0, 0 };//вектор вычисленных значений функций по ортам (нужно, чтобы потом выбрать тот орт, в направлении которого происходит
                              //наибольшее убывание функции)

double currF = 13;//значение функции в точке (0, 0, 0)

double m = 0;

//вычисляем числитель
double calculateNumerator(double mA[n][n],double currX[n], double mB[n], double mE[n]) {
    //вычисляем q = A*current_X+b, где A, current_X и b - матрицы
    double summ = 0;
    for (int i = 0; i < n; i++) {
        summ = 0;
        for (int j = 0; j < n; j++) {
            summ += mA[i][j] * currX[j];//а11*b1+a12*b2+a13*b3 
        }                               //a21*b1+a22*b2+a23*b3 etc
        mQ[i] = summ + mB[i];
        cout << "q[" << i << "] = " << mQ[i] << endl;
    }
    //умножаем орт e^T на вычисленное q (получаем число)
    double numerator = 0;
    for (int i = 0; i < n; i++) {
        numerator += mQ[i] * mE[i];
    }
    cout << "Result e^T*(Ax+b) (numerator): " << numerator << endl;

    return numerator;
}
//вычисляем знаменатель
double calculatedenominator(double mA[n][n],double mE[n]) {

    double mM[n] = { 0, 0, 0 };//вспомогательный вектор
    double summ = 0;
    //вычисляем А*е, где А - матрица, е - орт
    for (int i = 0; i < n; i++) {
        summ = 0;
        for (int j = 0; j < n; j++) {
            summ += mA[i][j] * mE[j];
        }
        mM[i] = summ;
        cout << "A*e[" << i << "] = " << mM[i] << endl;
    }
    //умножаем вектора e^T на вычисленное A*e (получаем число)
    double denominator = 0;
    for (int i = 0; i < n; i++) {
        denominator += mM[i] * mE[i];
    }
    cout << "Result e^T*Ae (denominator): " << denominator << endl;

    return denominator;
}
//вычисляем x_n = x_n-1 + m_n*e_n, а также значение функции в этой точке
double calculateX(double currX[n],double m, double mE[n]) {
    countX++;
    for (int i = 0; i < n; i++) {
        calcX[i] = currX[i] + m * mE[i];
        cout << "x_" << countX << "[" << i << "] = " << calcX[i] << endl;
    }
    double f = 2 * pow(calcX[0], 2) + 4.3 * pow(calcX[1], 2) + 5.3 * pow(calcX[2], 2) + calcX[0] * calcX[1] - calcX[1] * calcX[2] + calcX[0] * calcX[2] + calcX[0] - 2 * calcX[1] + 3 * calcX[2] + 13;
    return f;
}

int main()
{
    cout.precision(10);
    double mE[n] = { 0,0,0 };
    //первые три итерации - с разными ортами: (1,0,0); (0,1,0); (0,0,1)
    //и запоминаем в массив calcF значения фукнции в этих точках
    for (int i = 0; i < 3; i++) {
        mE[i] = 1;
        cout << endl;
        double k = calculateNumerator(mA, currX, mB, mE);
        double s = calculatedenominator(mA, mE);
        m = -k / s;//собираем мью для вычисления x_n = x_n-1 + m_n*e_n
        calcF[i] = calculateX(currX, m, mE);
        cout << "F: " << calcF[i] << endl;
        mE[i] = 0;
        for (int i = 0; i < n; i++) {//перезаписываем вычисленное решение в текущий вектор решений
            currX[i] = calcX[i];
        }
    }
    //после перебора всех координатных ортов от 1 до 3 в качестве очередного направления спуска назначаем тот орт, в направлении которого происходит
    //наибольшее убывание функции
    double delta = abs(currF-calcF[0]);//разница между занчением функции в точке (0,0,0) и в первой найденной точке
    int best_position = 0;
    for (int i = 0; i < 2; i++) {
        if (abs(calcF[i] - calcF[i + 1]) > delta) {
            delta = abs(calcF[i] - calcF[i + 1]);
            best_position = i + 1;
        }
    }
    cout << endl << "delta: " << delta << "  " << "position: " << best_position << endl;
    //перезаписывем наш орт на тот, в напрвлении которого происходит наибольшее убывание функции
    for (int i = 0; i < 3; i++) {
        mE[i] = 0;
    }
    mE[best_position] = 1;
    //вычисляем минимум, используя зафиксированный орт
    bool exit = false;
    while (exit == false) {
        cout << endl;
        double k = calculateNumerator(mA, currX, mB, mE);
        double s = calculatedenominator(mA, mE);
        m = -k / s;
        calculateX(currX, m, mE);
        //проверяем, пока все координаты решения на будут отличать менее чем на эпселон от предыдущего решения
        if ((abs(currX[0] - calcX[0]) <= eps) and (abs(currX[1] - calcX[1]) <= eps) and (abs(currX[2] - calcX[2]) <= eps)) {
            exit = true;
        }
        for (int i = 0; i < n; i++) {//перезаписываем вычисленное решение в текущий вектор решений
            currX[i] = calcX[i];
        }
    }
}
