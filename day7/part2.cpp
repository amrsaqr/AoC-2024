#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int64_t concat(int64_t x, int64_t y) {
    return x * (int64_t)pow(10, (int64_t)log10(y) + 1) + y;
}

bool canProduceTestValueHelper(const int64_t test, int64_t currentValue, const vector<int64_t>& numbers, int index) {
    if (index == numbers.size()) {
        return test == currentValue;
    }

    if (canProduceTestValueHelper(test, currentValue + numbers[index], numbers, index + 1)) {
        return true;
    }

    if (canProduceTestValueHelper(test, currentValue * numbers[index], numbers, index + 1)) {
        return true;
    }

    if (canProduceTestValueHelper(test, concat(currentValue, numbers[index]), numbers, index + 1)) {
        return true;
    }

    return false;
}

bool canProduceTestValue(const int64_t test, const vector<int64_t>& numbers) {
    return canProduceTestValueHelper(test, numbers[0], numbers, 1);
}

int main() {
    ifstream file("input.txt");

    int64_t sum = 0;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        int64_t test, n;
        char ch;
        vector<int64_t> numbers;

        iss >> test >> ch;
        while (iss >> n) {
            numbers.push_back(n);
        }

        if (canProduceTestValue(test, numbers)) {
            sum += test;
        }
    }

    cout << sum << endl;

    return 0;
}
