#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//[5,25]
int left_board = 5;
int right_board = 25;


vector<double> func(int n, vector<double>x) {//вектор значений, то есть f(x_i) = x_i * ln(x_i +1)
    vector<double> y (n);
    for (int i = 0; i < n; i++) {
        y[i] = x[i] * log(x[i] + 1);
    }
    return y;
}

vector<double> func_abs(int n, vector<double>x) {//вектор значений, то есть f(x_i) = abs(x_i) * x_i * ln(x_i +1)
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = abs(x[i]) * x[i] * log(x[i] + 1);
    }
    return y;
}


vector<double> vectorSum(vector<double> A, vector<double> B) { // функция, складывающая элементы матриц при соответствующий коэф
    vector<double>result(A.size(), 0);
    if (A.size() > B.size()) { //проверяем на одинаковость размерности матриц, если не сходятся, то увеличиваем меньшую, добавляя нули в конец
        B.resize(A.size(), 0);
    }
    else {
        A.resize(B.size(), 0);
    }
    for (int i = 0; i < A.size(); i++)
    {
        result[i] = A[i] + B[i];
    }
    return result;
}
vector<double> vectorMult(vector<double> A, double C) { // Функци, которая умножает все элементы матрицы на определенный коэф
    vector<double>result(A.size(), 0);
    for (int i = 0; i < A.size(); i++)
    {
        result[i] = A[i] * C;
    }
    return result;
}


// получение string из double
static string get_string_from_double(double num) {
    double num1 = abs(num);
    int sign = 1;
    int wh = (int)num1;
    double num2 = num1 - wh;

    string res = to_string(wh) + ".";

    if (num < 0) res = "-" + res;

    for (int i = 1; i < 25; i++) {
        num2 = num2 * 10;
        int xr = (int)num2;
        num2 = num2 - xr;
        res += to_string(xr);
    }
    while (res[res.length() - 1] == '0') {
        res = res.substr(0, res.length() - 1);
    }
    if (res[res.length() - 1] == '.') res += "0";
    return res;
}

void showPolynom(vector<double>& F) { //собираем полином Лагранжа в виде строки
    //string res;
    string res1;
    for (int i = 0; i < F.size(); i++)
    {
        if (i == 0) {
            //res += to_string(F[0]);
            res1 += get_string_from_double(F[0]);
        }
        else if (i == 1) {
            if (F[i] == 1) {
                //res += " + x";
                res1 += " + x";
            }
            else {
               // res += " + " + to_string(F[i]) + "*x";
                res1 += " + (" + get_string_from_double(F[i]) + ")*x";
            }
        }
        else {
            if (F[i] == 1) {
                //res += " + x^" + to_string(i);
                res1 += " + x^" + to_string(i);
            }
            else {
                //res += " + " + to_string(F[i]) + "*x^" + to_string(i);
                res1 += " + (" + get_string_from_double(F[i]) + ")*x^" + to_string(i);
            }
        }
    }
    res1 += "\n";
    replace(res1.begin(), res1.end(), ',', '.');
    cout << "L(x) = " << res1;
}
vector<double> Polinom(vector<double>& A, vector<double>& B) { // функция, которая умножает многочлен на многочлен( например (x-2)(x+2) = x^2 - 4)
    vector<double> result(A.size() + B.size() - 1, 0.0); // создаем массив, который будет размером, как максимальная степень одного плюс макс второго - 1
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B.size(); j++)
        {   // так как позиция элемента представляет собой степень x, а значение элемента коэф при соответсвующем x, то при умножении одного на другого степени складываются, а значения перемножаются
           // пример: (x + 5) = (5x^0 + 1x^1) будет представлять массив [5, 1]. Возьмем другой массив [5, 1]. на выходе функции у нас получится массив [25, 5 + 5, 1] = [25, 10, 1]
            // Если мы проведем умножение двух многочленов вручную, то получим (x+5)(x+5) = (x^2 + 5x +5x + 25) = (x^2+10x+25), что соответветсвует массиву [25,10,1]
            result[i + j] += A[i] * B[j];
        }
    }
    return result;
}
vector<double>  lagranz(vector<double> X, vector<double> Y) { //сама функция, которая считает  многочлен лангранжа 
    int size = X.size();
    vector<double> result(size, 0); // вспомогательные переменные
    vector<double> subResult;
    vector<double> subPolinom(2, 1);
    double C;
    for (int i = 0; i < size; i++)
    {
        C = Y[i]; // коэф при Yi
        subResult = { 1 }; //единичные многочлен, представляющий собой 1 
        for (int j = 0; j < size; j++)
        {
            if (i != j) {
                C /= (X[i] - X[j]); // тут мы вычисляем знаменатель П(Xi - Xj) i!=j
                subPolinom[0] = -X[j];  // создаем многочлен (X - Xj)
                subResult = Polinom(subResult, subPolinom); //перемножаем многочлены, чтобы получить коэф. П(X - Xj) i!=j
            }
        }
        subResult = vectorMult(subResult, C); // умножаем наш многочлен на константу
        result = vectorSum(result, subResult); // складываем полученные многочлены
    }
    return result; // возвращаем коэф многочлена лангранжа
}

vector<double> equal_nods(int n) {//находим равностоящие узлы
    cout << "Равностоящие узлы: " << endl;
    vector<double> x_equal(n);
    double k = 20 / n;//шаг для равностоящих узлов
    for (int i = 0; i < n; i++) {
        x_equal[i] = 5 + k * i;
        cout << "x[" << i << "] = " << x_equal[i] << endl;
    }
    return x_equal;
}

vector<double> cheb_nods(int n) {//находим чебышевские узлы
    cout << "Чебышевские узлы: " << endl;
    vector<double> x_cheb(n);
    double pi = 3.14159265358979323846;
    for (int i = 0; i < n; i++) {
        x_cheb[i] = 0.5 * ((right_board - left_board) * cos((double)(2 * i + 1) * pi / (2 * (n + 1))) + (right_board + left_board));
        cout << "x[" << i << "] = " << x_cheb[i] << endl;
    }
    return x_cheb;
}

void difference(int n, vector<double> x, vector<double> result, bool g) {//проверка, что значение исх функции и полинома лагранжа в узлах должны совпадать
    double h = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            h += result[i] * pow(x[j], i);
        }
        if (n > 14) {
            h = abs(x[j]) * x[j] * log(x[j] + 1);
        }
        if (g == true) {
            cout << "abs(L(x_" << j << ")-f(x_" << j << ")) = abs(" << h << " - " << abs(x[j]) * x[j] * log(x[j] + 1) << ") == 0" << endl; }
        else {
            cout << "abs(L(x_" << j << ")-f(x_" << j << ")) = abs(" << h << " - " << x[j] * log(x[j] + 1) << ") == 0" << endl;}
        h = 0;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout.precision(6);
    bool g = false;
    int n = 0;
    cout << "Введите количество узлов:\n";
    cin >> n;
    cout << "x*ln(x+1)" << endl;

    //создаем массив из n равностоящих узлов
    vector<double> x_equal = equal_nods(n);
    cout << endl;
    vector<double> y_equal = func(n, x_equal);

    for (int i = 0; i < n; i++) {
        cout << "y[" << i << "] = " << y_equal[i] << endl;
    }
    cout << endl;
    vector<double> result = lagranz(x_equal, y_equal); // передаем значения
    showPolynom(result); // выводим результат
    difference(n, x_equal, result, g);

    //создаем массив из n чебышевских узлов
    vector<double> x_cheb = cheb_nods(n);
    cout << endl;
    vector<double> y_cheb = func(n, x_cheb);
    for (int i = 0; i < n; i++) {
        cout << "y[" << i << "] = " << y_cheb[i] << endl;
    }
    cout << endl;
    vector<double> result_cheb = lagranz(x_cheb, y_cheb); // передаем значения
    showPolynom(result_cheb); // выводим результат
    difference(n, x_cheb, result_cheb, g);

    for (int i = 0; i < n; i++) {
        x_equal[i] = 0;
        y_equal[i] = 0;
        x_cheb[i] = 0;
        y_cheb[i] = 0;
    }

    cout << endl << "abs(x)*x*ln(x+1)" << endl;
    g = true;
    //создаем массив из n равностоящих узлов
    x_equal = equal_nods(n);
    cout << endl;
    vector<double> y_equal_abs = func_abs(n, x_equal);

    for (int i = 0; i < n; i++) {
        cout << "y[" << i << "] = " << y_equal_abs[i] << endl;
    }
    cout << endl;
    vector<double> result_abs = lagranz(x_equal, y_equal_abs); // передаем значения
    showPolynom(result_abs); // выводим результат
    difference(n, x_equal, result_abs, g);

    x_cheb = cheb_nods(n);
    cout << endl;
    vector<double> y_cheb_abs = func_abs(n, x_cheb);
    for (int i = 0; i < n; i++) {
        cout << "y[" << i << "] = " << y_cheb_abs[i] << endl;
    }
    cout << endl;
    vector<double> result_cheb_abs = lagranz(x_cheb, y_cheb_abs); // передаем значения
    showPolynom(result_cheb_abs); // выводим результат
    difference(n, x_cheb, result_cheb_abs, g);
}
