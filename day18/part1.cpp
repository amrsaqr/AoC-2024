#include <iostream>
#include <fstream>
using namespace std;

class BytePos {
public:
    BytePos(int i, int j, int steps) : i{i}, j{j}, steps{steps} {
    }

    int i, j, steps;
};

class RamSolver {
public:
    RamSolver(int r, int c) : r{r}, c{c}, ram(r, string(c, '.')) {
    }

    void byteFall(int x, int y) {
        ram[y][x] = '#';
    }

    int solve() {
        queue<BytePos> bfs;
        vector<vector<bool>> occupied(r, vector<bool>(c, false));
        bfs.emplace(0, 0, 0);
        occupied[0][0] = true;

        while (!bfs.empty()) {
            auto pos = bfs.front();
            bfs.pop();

            if (pos.i == r - 1 && pos.j == c - 1) {
                return pos.steps;
            }

            for (int d = 0; d < 4; ++d) {
                int ni = pos.i + di[d];
                int nj = pos.j + dj[d];

                if (insideRam(ni, nj) && ram[ni][nj] != '#' && !occupied[ni][nj]) {
                    bfs.emplace(ni, nj, pos.steps + 1);
                    occupied[ni][nj] = true;
                }
            }
        }

        return -1;
    }

private:
    bool insideRam(int i, int j) {
        return i >= 0 && i < r && j >= 0 && j < c;
    }

    const int r;
    const int c;
    vector<string> ram;
    static constexpr int di[4]{0, 0, 1, -1};
    static constexpr int dj[4]{1, -1, 0, 0};
};

int main() {
    ifstream file("input.txt");

    const int r = 71, c = 71;
    RamSolver ramSolver(r, c);
    int x, y;
    char skip;
    const int bytes = 1024;
    for (int byte = 0; byte < bytes && file >> x >> skip >> y; ++byte) {
        ramSolver.byteFall(x, y);
    }

    cout << ramSolver.solve() << endl;

    return 0;
}