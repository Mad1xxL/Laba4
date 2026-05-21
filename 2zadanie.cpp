#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void printVector(const vector<int>& values, const string& title) {
    cout << title << ": ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
}

vector<int> generateArray(int n, int left, int right) {
    random_device rd;
    uniform_int_distribution<int> dist(left, right);
    vector<int> values;
    for (int i = 0; i < n; i++) {
        values.push_back(dist(rd));
    }
    return values;
}

int main() {
    int n;
    cout << "Введите n для первого массива, n >= 10: ";
    cin >> n;

    if (n < 10) {
        cout << "Ошибка: n должно быть не меньше 10\n";
        return 1;
    }

    vector<int> arr = generateArray(n, 0, 100);
    printVector(arr, "Исходный массив");

    int sumEvenAfterOdd = 0;
    vector<int> evenAfterOdd;
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] % 2 == 0 && arr[i - 1] % 2 != 0) {
            evenAfterOdd.push_back(arr[i]);
            sumEvenAfterOdd += arr[i];
        }
    }

    printVector(evenAfterOdd, "Четные элементы после нечетных");
    cout << "Сумма таких элементов: " << sumEvenAfterOdd << '\n';

    vector<int> localMinimums;

    for (size_t i = 1; i + 1 < arr.size(); i++) {
        if (arr[i] < arr[i - 1] && arr[i] < arr[i + 1]) {
            localMinimums.push_back(arr[i]);
        }
    }

    printVector(localMinimums, "Локальные минимумы");

    vector<int> evens;
    vector<int> odds;

    for (int value : arr) {
        if (value % 2 == 0) {
            evens.push_back(value);
        } else {
            odds.push_back(value);
        }
    }

    sort(evens.begin(), evens.end());
    sort(odds.begin(), odds.end(), greater<int>());

    size_t evenIndex = 0;
    size_t oddIndex = 0;

    vector<int> sortedByParity = arr;

    for (int& value : sortedByParity) {
        if (value % 2 == 0) {
            value = evens[evenIndex];
            evenIndex++;
        } else {
            value = odds[oddIndex];
            oddIndex++;
        }
    }

    printVector(sortedByParity, "Массив после сортировки четных и нечетных элементов");

    int m;
    cout << "\nВведите n для второго массива, n >= 15: ";
    cin >> m;
    if (m < 15) {
        cout << "Ошибка: n должно быть не меньше 15\n";
        return 1;
    }

    vector<int> secondArray = generateArray(m, 100, 120);
    printVector(secondArray, "Второй массив");

    vector<int> count(121, 0);

    for (int value : secondArray) {
        count[value]++;
    }

    int mostFrequent = secondArray[0];
    for (int value : secondArray) {
        if (count[value] > count[mostFrequent]) {
            mostFrequent = value;
        }
    }

    cout << "Чаще всего встречается элемент: " << mostFrequent << '\n';
    cout << "Количество повторений: " << count[mostFrequent] << '\n';

    vector<int> greaterThanMostFrequent;
    for (int value : secondArray) {
        if (value > mostFrequent) {
            greaterThanMostFrequent.push_back(value);
        }
    }

    printVector(greaterThanMostFrequent, "Элементы больше наиболее частого");

    return 0;
}