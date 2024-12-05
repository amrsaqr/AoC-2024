#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool isSafe(const vector<int>& numbers) {
    int n = (int)numbers.size();
    bool safe = false;

    for (int skip = -1; skip < n && !safe; ++skip) {
        const int* last = nullptr;
        bool differsBy1To3 = true;
        bool strictlyIncreasing = true;
        bool strictlyDecreasing = true;

        for (int i = 0; i < n; ++i) {
            if (i == skip) {
                continue;
            }

            if (last) {
                int diff = abs(numbers[i] - *last);
                if (diff < 1 || diff > 3) {
                    differsBy1To3 = false;
                    break;
                }
            }


            if (last && numbers[i] <= *last) {
                strictlyIncreasing = false;
            }

            if (last && numbers[i] >= *last) {
                strictlyDecreasing = false;
            }

            if (!strictlyIncreasing && !strictlyDecreasing) {
                break;
            }

            last = &numbers[i];
        }

        safe = differsBy1To3 && (strictlyIncreasing || strictlyDecreasing);
    }

    return safe;
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
