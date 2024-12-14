#include <iostream>
#include <fstream>
#include <list>
using namespace std;

int main() {
    ifstream file("input.txt");

    list<int64_t> nums;
    for (int64_t num; file >> num; ) {
        nums.push_back(num);
    }

    auto getDigitsCount = [](int64_t num) {
        return (int)log10(num) + 1;
    };

    for (int blink = 1; blink <= 25; ++blink) {
        auto it = nums.begin();
        while (it != nums.end()) {
            if (*it == 0) {
                *it++ = 1;
            } else {
                int digitsCount = getDigitsCount(*it);
                if (digitsCount % 2) {
                    *it++ *= 2024;
                } else {
                    int p = (int)pow(10, digitsCount / 2);
                    int64_t left = *it / p;
                    int64_t right = *it % p;

                    *it++ = left;
                    nums.insert(it, right);
                }
            }
        }
    }

    cout << nums.size() << endl;

    return 0;
}
