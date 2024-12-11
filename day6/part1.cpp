#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> map;
    while (getline(file, line)) {
        map.push_back(line);
    }

    int r = (int)map.size();
    int c = (int)map[0].size();
    auto inMap = [&r, &c](int i, int j) {
        return i >= 0 && i < r && j >= 0 && j < c;
    };

    int i;
    int j;
    bool guardFound = false;
    for (i = 0; i < r; ++i) {
        for (j = 0; j < c; ++j) {
            if (map[i][j] == '^') {
                guardFound = true;
                break;
            }
        }

        if (guardFound) {
            break;
        }
    }

    int dir = 0;
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0,  1, 0, -1};

    int count = 0;
    while (true) {
        if (map[i][j] != 'X') {
            map[i][j] = 'X';
            ++count;
        }

        for (int trials = 0; trials < 4; ++trials) {
            i += di[dir];
            j += dj[dir];

            if (inMap(i, j) && map[i][j] == '#') {
                i += (di[dir] * -1);
                j += (dj[dir] * -1);
                dir = (dir + 1) % 4;
            } else {
                break;
            }
        }

        if (!inMap(i, j)) {
            break;
        }
    }

    cout << count << endl;

    return 0;
}
