#include <iostream>
#include <vector>

using namespace std;

int modValue(int value, int m) {
    value %= m;

    if (value < 0) {
        value += m;
    }

    return value;
}

int calculateNext(int x, int y, char operation, int m) {
    if (operation == '+') {
        return modValue(x + y, m);
    }

    if (operation == '-') {
        return modValue(x - y, m);
    }

    if (operation == '*') {
        return modValue(x * y, m);
    }

    if (operation == '^') {
        return modValue(x ^ y, m);
    }

    return 0;
}

int main() {
    int n;
    cout << "Введите количество чисел N: ";
    cin >> n;

    int a;
    cout << "Введите лаг a: ";
    cin >> a;

    int b;
    cout << "Введите лаг b: ";
    cin >> b;

    int m;
    cout << "Введите модуль m: ";
    cin >> m;

    char operation;
    cout << "Введите операцию (+, -, *, ^): ";
    cin >> operation;

    int initialCount = max(a, b);

    vector<int> sequence(initialCount);

    cout << "Введите " << initialCount << " начальных значений:\n";

    for (int& value : sequence) {
        cin >> value;
        value = modValue(value, m);
    }

    while (static_cast<int>(sequence.size()) < n) {
        int currentIndex = sequence.size();

        int x = sequence[currentIndex - a];
        int y = sequence[currentIndex - b];

        int next = calculateNext(x, y, operation, m);
        sequence.push_back(next);
    }

    cout << "Сгенерированная последовательность:\n";

    for (int value : sequence) {
        cout << value << ' ';
    }

    cout << '\n';

    return 0;
}