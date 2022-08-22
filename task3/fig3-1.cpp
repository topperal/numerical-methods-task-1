#include <iostream>
#include <cmath>
using namespace std;

int n = 100;
double right_board = 1;
double left_board = -1;
double eps = 0.0001;

double my_function(double x) {              // x ln(x + 1) − 0.3
    return (x * log(x + 1) - 0.3);
}

double first_derivate(double x) {
    return (x / (x + 1) + log(x + 1));
}

double second_derivate(double x) {
    return ((-x / (x + 1) + 2) / (x + 1));
}

double h_function(double x) {
    return (-my_function(x)/ first_derivate(x));
}

int main()
{
   cout.precision(9);
   double previous_x = -1;
   double x_k;  double root1 = 0;  double root2 = 0;
   cout << "[" << left_board << "; " << right_board << "]" << endl;
   for (int k = 0; k <= n; k++) {
       x_k = left_board + k * (right_board - left_board) / n;
       cout << "x_" << k << ": " << x_k << endl;
       if (my_function(x_k) * my_function(previous_x) < 0) {
           if (root1 == 0) { root1 = x_k; }
           else { root2 = x_k; }
       }
       previous_x = x_k;
   }
   cout << "root1:  " << root1 << endl << "root2:  " << root2 << endl;
   double next = 0;
   double root;
   if (fabs(root1) < fabs(root2)) { root = root1; }
   else {   root = root2;   }
   cout << "min|root|: " << root << endl;
   cout << "|f(x_k)/f'(x_k)| < 0.0001" << endl;
   cout << "x_n: " << root << endl;
   while (fabs(h_function(root)) >= eps) {
           next = root + h_function(root);
           root = next;
           cout << "x_n: " << next << endl;
    }
    cout << endl << "root: " << root << endl << "f(root): " << my_function(next + h_function(next)) << endl;
}
