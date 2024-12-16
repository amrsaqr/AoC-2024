#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    const int secs = 100;
    const int r = 103;
    const int c = 101;
    const pair<int, int> quadrants[4][2] {
            {{0, r / 2 - 1}, {0, c / 2 - 1}},
            {{0, r / 2 - 1}, {c / 2 + 1, c - 1}},
            {{r / 2 + 1, r - 1}, {0, c / 2 - 1}},
            {{r / 2 + 1, r - 1}, {c / 2 + 1, c - 1}}
    };
    int counts[4]{0, 0, 0, 0};
    char ch;

    for (int i, j, di, dj; file >> ch >> ch >> j >> ch >> i >> ch >> ch >> dj >> ch >> di; ) {
        i += di * secs;
        j += dj * secs;

        i %= r;
        if (i < 0) {
            i += r;
        }

        j %= c;
        if (j < 0) {
            j += c;
        }

        for (int k = 0; k < 4; ++k) {
            if (i >= quadrants[k][0].first && i <= quadrants[k][0].second && j >= quadrants[k][1].first && j <= quadrants[k][1].second) {
                ++counts[k];
                break;
            }
        }
    }

    cout << counts[0] * counts[1] * counts[2] * counts[3] << endl;

    return 0;
}