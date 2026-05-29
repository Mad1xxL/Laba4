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

void sqrtNaOtrezke(double a, double b) {
    cout << "\nМетод половинного деления\n";
    cout << setw(5) << "N"
         << setw(15) << "a(n)"
         << setw(15) << "b(n)"
         << setw(15) << "b(n)-a(n)" << '\n';

    int n = 0;

    while (abs(b - a) > EPS) {
        double seredina = (a + b) / 2;

        if (f(a) * f(seredina) <= 0) {
            b = seredina;
        } else {
            a = seredina;
        }

        cout << setw(5) << ++n
             << setw(15) << a
             << setw(15) << b
             << setw(15) << abs(b - a) << '\n';
    }

    cout << "Корень: " << (a + b) / 2 << '\n';
}

void newton(double x0) {
    cout << "\nМетод Ньютона\n";
    cout << setw(5) << "N"
         << setw(15) << "x(n)"
         << setw(15) << "x(n+1)"
         << setw(15) << "x(n+1)-x(n)" << '\n';

    int n = 0;

    while (true) {
        double x1 = x0 - f(x0) / df(x0);

        cout << setw(5) << n
             << setw(15) << x0
             << setw(15) << x1
             << setw(15) << abs(x1 - x0) << '\n';

        if (abs(x1 - x0) <= EPS) {
            cout << "Корень: " << x1 << '\n';
            break;
        }

        x0 = x1;
        n++;
    }
}

void simpleIterations(double x0) {
    cout << "\nМетод простых итераций\n";
    cout << setw(5) << "N"
         << setw(15) << "x(n)"
         << setw(15) << "x(n+1)"
         << setw(15) << "x(n+1)-x(n)" << '\n';

    int n = 0;

    while (true) {
        double x1 = phi(x0);

        cout << setw(5) << n
             << setw(15) << x0
             << setw(15) << x1
             << setw(15) << abs(x1 - x0) << '\n';

        if (abs(x1 - x0) <= EPS) {
            cout << "Корень: " << x1 << '\n';
            break;
        }

        x0 = x1;
        n++;
    }
}

int main() {
    cout << fixed << setprecision(6);

    double a = -1;
    double b = 0;

    sqrtNaOtrezke(a, b);
    newton(-1);
    simpleIterations(-1);

    return 0;
}