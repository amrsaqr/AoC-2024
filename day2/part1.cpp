#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool isSafe(const vector<int>& numbers) {
    bool differsBy1To3 = true;
    bool strictlyIncreasing = true;
    bool strictlyDecreasing = true;

    for (int i = 1; i < numbers.size(); ++i) {
        int diff = abs(numbers[i] - numbers[i - 1]);
        if (diff < 1 || diff > 3) {
            differsBy1To3 = false;
            break;
        }

        if (numbers[i] <= numbers[i - 1]) {
            strictlyIncreasing = false;
        }

        if (numbers[i] >= numbers[i - 1]) {
            strictlyDecreasing = false;
        }

        if (!strictlyIncreasing && !strictlyDecreasing) {
            break;
        }
    }

    return differsBy1To3 && (strictlyIncreasing || strictlyDecreasing);
}

int main() {
    ifstream file("input.txt");

    int safe = 0;
    string line;

    while (getline(file, line)) {
        int n;
        vector<int> numbers;
        istringstream iss(line);

        while (iss >> n) {
            numbers.push_back(n);
        }

        if (isSafe(numbers)) {
            ++safe;
        }
    }

    cout << safe << endl;

    return 0;
}
