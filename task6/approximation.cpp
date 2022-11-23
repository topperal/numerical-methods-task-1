#include <iostream>
using namespace std;

int n = 4;
double equalDistanceX[5] = { -1,-0.4,0,0.6,0.9 };
double equalDistanceY[5] = { 0, 0, 0, 0, 0 };
double mA[4][4] = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
};
double mB[4];
double mRes[4] = { 0, 0, 0, 0 };

void func() {
    for (int i = 0; i < 5; i++) {
        equalDistanceY[i] = equalDistanceX[i] * tan(equalDistanceX[i]);
        cout << "x_" << i << ": " << equalDistanceX[i] << endl << "y_" << i << ": " << equalDistanceY[i] << endl;
    }
}

void coeff() {//коэфф в МНК
    double sixthX = 0;
    double fifthX = 0;
    double fourthX = 0;
    double thirdX = 0;
    double squareX = 0;
    double generalX = 0;
    double multyThirdXandY = 0;
    double multySquareXandY = 0;
    double multyXandY = 0;
    double generalY = 0;
    double vecX[6];
    for (int i = 0; i < 5; i++) {
        sixthX += pow(equalDistanceX[i], 6);
        vecX[0] = sixthX;
        fifthX += pow(equalDistanceX[i], 5);
        vecX[1] = fifthX;
        fourthX += pow(equalDistanceX[i], 4);
        vecX[2] = fourthX;
        thirdX += pow(equalDistanceX[i], 3);
        vecX[3] = thirdX;
        squareX += pow(equalDistanceX[i], 2);
        vecX[4] = squareX;
        generalX += equalDistanceX[i];
        vecX[5] = generalX;
        multyThirdXandY += pow(equalDistanceX[i], 3) * equalDistanceY[i];
        mB[0] = multyThirdXandY;
        multySquareXandY += pow(equalDistanceX[i], 2) * equalDistanceY[i];
        mB[1] = multySquareXandY;
        multyXandY += equalDistanceX[i] * equalDistanceY[i];
        mB[2] = multyXandY;
        generalY += equalDistanceY[i];
        mB[3] = generalY;
    }

    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mA[i][j] = vecX[j + count];
        }
        count++;
    }
    mA[3][3] = 5;

    for (int i = 0; i < 4; i++) {
        cout << endl;
        for (int j = 0; j < 4; j++) {
            cout << mA[i][j] << "      ";
        }  
    }

    cout << endl << "\nx^6: " << sixthX << "  x^5: " << fifthX << "   x^4: " << fourthX << " x^3: " << thirdX << "  x^2: " << squareX << "  x:  " << generalX << endl;
    cout << "x^3*y: " << multyThirdXandY << "  x^2*y: " << multySquareXandY << " x*y: " << multyXandY << "  y: " << generalY << endl;

}

void mPrint() {                             // вывод матрицы 
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mA[i][j] << " ";
        }
        cout << " = " << mB[i];
        cout << endl;
    }
}

// НАЧАЛО МЕТОДА ГАУССА
void mDivisionRaw(int nraw, int ncolumn) {          // делим строку на первый элемент
    double start = mA[nraw][ncolumn];//определяем первый элементр в строке, на который делим все ост элементы в строке
    if (start != 0) {//если элемент, на который делим, не ноль, то начинаем деление
    for (int i = ncolumn; i < n; i++) {
        mA[nraw][i] /= start;
    }
    mB[nraw] /= start;
    mPrint();//выводим матрицу, с которой работаем
    }
}

void mSub(int nraw) {                               // вычитаем предыдущую строку
    for (int i = nraw + 1; i < n; i++) {
        mDivisionRaw(i, nraw);//делим строку на первый ненулевый элемент, чтобы 1-ый эл стал = 1
        for (int j = 0; j < n; j++) {
            mA[i][j] -= mA[nraw][j];
        }
        mB[i] = mB[i] - mB[nraw];
    }
    mPrint();
}

void mFind(int nraw) {                          // находим решения
    double res = 0;
    for (int i = nraw; i < n; i++) {
        res += mA[nraw][i] * mRes[i];
    }
    mRes[nraw] = mB[nraw] - res;
}
// КОНЕЦ МЕТОДА ГАУССА

// ПРИБЛИЖЕНИЕ МНОГОЧЛЕНАМИ ЛЕЖАНДРА
double mL0[5] = {1, 0, 0, 0, 0};//L_0 = 1
double mL1[5] = {0, 1, 0, 0, 0};//L_1 = x
double mL2[5] = {-0.5, 0, 1.5, 0, 0};//L_2 = -0.5+1.5*x^2
double mL3[5] = {0, -1.5, 0, 2.5, 0};//L_3 = -1.5*x + 2.5*x^3
double mL4[5] = {0.375, 0, -3.75, 0, 4.375};//L_4 = 3/8 - 15/4*x^2 + 35/8*x^4

double mC[5] = { 0.428, 0, 0.95, 0, 0.03187 };//коээфициенты с для полиномов Лежандра

void calcQ() {//вычилсяем многочлен Лежандра, который является частным случаем ортогональных полиномов
    double mQ[5] = { 0,0,0,0,0 };
    for (int i = 0; i < 5; i++) {
        mQ[i] += mC[0] * mL0[i] + mC[1] * mL1[i] + mC[2] * mL2[i] + mC[3] * mL3[i] + mC[4] * mL4[i];//Q_4 = c_0*Q_0 + c_1*Q_1 + c_2*Q_2 + c_3*Q_3 + c_4*Q_4
    }
    cout << endl << "Q_4(x) = L_4(x) = x^4 * (" << mQ[4] << ") + x^3 * (" << mQ[3] << ") + x^2 * (" << mQ[2] << ") + x * (" << mQ[1] << ") + (" << mQ[0] << ")" << endl;
}

int main()
{
    cout.precision(6);
    func();//вычисляем значение функции в точках
    coeff();//вычиялем коэфф a_i, b_i, c_i, d_ i, res_i
    //a*summ(x^6) + b*summ(x^5) + c*summ(x^4) + d*summ(x^3) = summ(x^3*y)
    //a*summ(x^5) + b*summ(x^4) + c*summ(x^3) + d*summ(x^2) = summ(x^2*y)
    //a*summ(x^4) + b*summ(x^3) + c*summ(x^2) + d*summ(x)   = summ(x*y)
    //a*summ(x^3) + b*summ(x^3) + c*summ(x)   + d*n         = summ(y), где n = 5 - число корней
    // МЕТОД ГАУССА
    mDivisionRaw(0, 0); // x + a12/a11 y + a13/a11 = b1/a11

    for (int i = 1; i < n; i++) {
        mSub(i - 1);
        for (int j = i; j < n; j++) {
            mDivisionRaw(j, i);
        }
    }

    mRes[n - 1] = mB[n - 1];

    mDivisionRaw(3, 3);
    for (int i = n - 2; i >= 0; i--) {
        mFind(i);
    }
    // КОНЕЦ МЕТОДА ГАУССА
    cout << endl << "P_3(x) = x^3*(" << mRes[0] << ") + x^2 * (" << mRes[1] << ") + x * (" << mRes[2] << ") + (" << mRes[3] << ")" << endl;

    double sigma = 0;

    for (int i = 0; i < 5; i++) {
        sigma += pow((mRes[0] * equalDistanceX[i] * equalDistanceX[i] * equalDistanceX[i] + mRes[1] * equalDistanceX[i] * equalDistanceX[i] + mRes[2] * equalDistanceX[i] + mRes[3]) - equalDistanceY[i], 2);
    }
    //cout << "sigma: " << sigma << endl;

    double delta = sqrt(sigma / 6);
    //cout << "delta: " << delta << endl;

    calcQ();
}
