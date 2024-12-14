#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main() {
    ifstream file("input.txt");

    unordered_map<int64_t, int64_t> nums[2];
    for (int64_t num; file >> num; ) {
        ++nums[0][num];
    }

    auto getDigitsCount = [](int64_t num) {
        return (int)log10(num) + 1;
    };

    for (int blink = 1, from = 0; blink <= 75; ++blink, from = 1 - from) {
        int to = 1 - from;
        nums[to].clear();

        for (const auto& num : nums[from]) {
            if (num.first == 0) {
                nums[to][1] += num.second;
            } else {
                int digitsCount = getDigitsCount(num.first);
                if (digitsCount % 2) {
                    nums[to][num.first * 2024] += num.second;
                } else {
                    int p = (int)pow(10, digitsCount / 2);
                    int64_t left = num.first / p;
                    int64_t right = num.first % p;

                    nums[to][left] += num.second;
                    nums[to][right] += num.second;
                }
            }
        }
    }

    int64_t count = 0;
    for (const auto& num : nums[1]) {
        count += num.second;
    }

    cout << count << endl;

    return 0;
}
