#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-4;

double f(double x) {
    return 2 * x + cos(x);
}

double df(double x) {
    return 2 - sin(x);
}

double phi(double x) {
    return -cos(x) / 2;
}

void bisection(double a, double b) {
    cout << "\nМетод половинного деления\n";
    cout << setw(5) << "N"
         << setw(15) << "an"
         << setw(15) << "bn"
         << setw(15) << "bn - an" << '\n';

    int n = 0;

    while (fabs(b - a) > EPS) {
        double c = (a + b) / 2;

        if (f(a) * f(c) <= 0) {
            b = c;
        } else {
            a = c;
        }

        cout << setw(5) << ++n
             << setw(15) << a
             << setw(15) << b
             << setw(15) << fabs(b - a) << '\n';
    }

    cout << "Корень: " << (a + b) / 2 << '\n';
}

void newton(double x0) {
    cout << "\nМетод Ньютона\n";
    cout << setw(5) << "N"
         << setw(15) << "xn"
         << setw(15) << "xn+1"
         << setw(15) << "xn+1 - xn" << '\n';

    int n = 0;
    double x1;

    do {
        x1 = x0 - f(x0) / df(x0);

        cout << setw(5) << n
             << setw(15) << x0
             << setw(15) << x1
             << setw(15) << fabs(x1 - x0) << '\n';

        x0 = x1;
        n++;
    } while (fabs(x1 - x0) > EPS);
}

void simpleIterations(double x0) {
    cout << "\nМетод простых итераций\n";
    cout << setw(5) << "N"
         << setw(15) << "xn"
         << setw(15) << "xn+1"
         << setw(15) << "xn+1 - xn" << '\n';

    int n = 0;
    double x1;

    do {
        x1 = phi(x0);

        cout << setw(5) << n
             << setw(15) << x0
             << setw(15) << x1
             << setw(15) << fabs(x1 - x0) << '\n';

        if (fabs(x1 - x0) <= EPS) {
            break;
        }

        x0 = x1;
        n++;
    } while (true);

    cout << "Корень: " << x1 << '\n';
}

int main() {
    cout << fixed << setprecision(6);

    double a = -1;
    double b = 0;

    bisection(a, b);
    newton(-1);
    simpleIterations(-1);

    return 0;
}