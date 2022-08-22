#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

ofstream fout;

double function(double x) {
    double z = atan(sqrt(1 + 0.9 * x)/(1 - pow(x,2))) + sin(0.6 + 3 * x);
    return z;
}

double factorial(int n) {
    if (n < 0) 
        return 0;
    if (n == 0) 
        return 1; 
    else 
        return n * factorial(n - 1); 
}

double approximate_sin(double x, int n) {           // приближенное вычисление значения синуса
    double appsin = 0;
    for (int k = 0; k < n; k++) {
        appsin += pow(-1, k) * pow(x, 2*k + 1) / factorial(2*k + 1);
    }
    return appsin;
}

double approximate_cos(double x, int n) {           // приближенное вычисление значения синуса
    double appsin = 0;
    for (int k = 0; k < n; k++) {
        appsin += pow(-1, k) * pow(x, 2 * k ) / factorial(2 * k);
    }
    return appsin;
}

double approximate_atan(double x, int n) {            // приближенное вычисление значения арктангенса
    double appatan = 0;
    double temp;
    for (int k = 0; k < n; k++) {
        temp = 2 * double(k) + 1;
        appatan += (pow(-1, k) * pow(x, -(2 * k + 1)) / temp);
    }
    appatan = M_PI / 2  - appatan;
    return appatan;
}

double heron(double a, double eps) {            // приближенное вычисление корня
    double xn = 0;
    double xn1 = 1;
    do { xn = xn1; xn1 = (xn + a / xn) / 2; } while (fabs(xn1 - xn) >= eps);
    return xn1;
}

int main()
{
    fout.open("file.csv", ios::app);
    const double rboard = 0.2;
    const double lboard = 0.3;
    const double step = 0.01;
    const double eps1 = pow(10, -6)/3; // погрешность для sqrt(1 + 0.9 * x)
    const double eps2 = pow(10, -6)/3;  // погрешность для sin(0.6 + 3 * x)
    const double eps3 = pow(10, -6)/3;    // погрешность для арктангенса
    const int count_sin = 5;              // мин кол-во членов в ряде маклорена для синуса
    const int count_atan = 54;            // мин кол-во членов в ряде маклорена для арктангенса
    const int count_cos = 3;              // мин кол-во членов в ряде маклорена для косинуса
    printf("   x |          z*(x) |           z(x) |       diff\n");
    fout << "значение x; приближенное знач. функции z*(x); точное знач. функции z(x); разность значений функций" << endl;
    for (double x = rboard; x < lboard+step; x+=step) {
        double app_func = approximate_atan(heron(1 + 0.9 * x, eps1)/ (1 - pow(x, 2)), count_atan) + approximate_cos(M_PI / 2 - (0.6 + 3 * x), count_cos);
        double func = function(x);
        double diff = fabs(app_func - func);
        printf("%.2f | %.12f | %.12f | %.4e\n", x, app_func, func, diff);
        fout << x << ";" << app_func << ";" << func << ";" << diff << "; " << endl;
    }
    fout.close();
}

