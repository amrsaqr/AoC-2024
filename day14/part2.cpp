#include <iostream>
#include <fstream>
using namespace std;

struct Pos {
    Pos(int i, int j, int di, int dj) : i{i}, j{j}, di{di}, dj{dj} {
    }

    void oneSecondMove(int r, int c) {
        i += di;
        i %= r;
        if (i < 0) {
            i += r;
        }

        j += dj;
        j %= c;
        if (j < 0) {
            j += c;
        }
    }

    int i, j;
    const int di, dj;
};

void printMap(const vector<vector<bool>>& map) {
    int r = (int)map.size();
    int c = (int)map[0].size();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (map[i][j]) {
                cout << '*';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ifstream file("input.txt");

    const int r = 103;
    const int c = 101;

    char ch;
    vector<Pos> robots;
    for (int i, j, di, dj; file >> ch >> ch >> j >> ch >> i >> ch >> ch >> dj >> ch >> di; ) {
        robots.emplace_back(i, j, di, dj);
    }

    bool possiblyFoundXmasTree = false;
    vector<vector<bool>> occ[2]{vector<vector<bool>>(r, vector<bool>(c, false)), vector<vector<bool>>(r, vector<bool>(c, false))};
    for (int second = 1, from = 0, to = 1; second <= 10000 && !possiblyFoundXmasTree; ++second, from ^= 1, to ^= 1) {
        for (auto& robot : robots) {
            occ[from][robot.i][robot.j] = false;
            robot.oneSecondMove(r, c);
            occ[to][robot.i][robot.j] = true;
        }

        for (int i = 50; i < r; ++i) {
            bool consecutive = true;
            for (int j = 45; j <= 55; ++j) {
                if (!occ[to][i][j]) {
                    consecutive = false;
                    break;
                }
            }

            if (consecutive) {
                possiblyFoundXmasTree = true;
                cout << "Second #" << second << endl;
                printMap(occ[to]);
                break;
            }
        }
    }

    if (possiblyFoundXmasTree) {
        cout << "Does the map above contain a Christmas tree?" << endl;
    }

    return 0;
}