#include <iostream>
#include <fstream>
using namespace std;

class MapSolver {
public:
    explicit MapSolver(vector<string>&& map) : map(map) {
        r = (int)map.size();
        c = (int)map[0].size();
        si = -1;
        sj = -1;
    }

    int solve() {
        findStartingPoint();
        return traverseAndGetObstacles();
    }

private:
    void findStartingPoint() {
        bool guardFound = false;
        for (int i = 0; i < r && !guardFound; ++i) {
            for (int j = 0; j < c && !guardFound; ++j) {
                if (map[i][j] == '^') {
                    si = i;
                    sj = j;
                    guardFound = true;
                }
            }
        }
    }

    int traverseAndGetObstacles() {
        int count = 0;
        vector<vector<bool>> obstacle(r, vector<bool>(c, false));

        for (int i = si, j = sj, dir = 0; true; ) {
            if (!obstacle[i][j] && !(i == si && j == sj)) {
                map[i][j] = '#';
                if (traverseAndCheckCycle(si, sj)) {
                    obstacle[i][j] = true;
                    ++count;
                }
                map[i][j] = '.';
            }

            for (int trials = 0; trials < 4; ++trials) {
                i += di[dir];
                j += dj[dir];

                if (inMap(i, j) && map[i][j] == '#') {
                    i -= di[dir];
                    j -= dj[dir];
                    dir = (dir + 1) % 4;
                } else {
                    break;
                }
            }

            if (!inMap(i, j)) {
                break;
            }
        }

        return count;
    }

    bool traverseAndCheckCycle(int i, int j) {
        vector<vector<vector<bool>>> vis(r, vector<vector<bool>>(c, vector<bool>(4, false)));
        for (int dir = 0; true; ) {
            if (vis[i][j][dir]) {
                return true;
            }
            vis[i][j][dir] = true;

            for (int trials = 0; trials < 4; ++trials) {
                i += di[dir];
                j += dj[dir];

                if (inMap(i, j) && map[i][j] == '#') {
                    i -= di[dir];
                    j -= dj[dir];
                    dir = (dir + 1) % 4;
                } else {
                    break;
                }
            }

            if (!inMap(i, j)) {
                break;
            }
        }

        return false;
    }

    bool inMap(int i, int j) const {
        return i >= 0 && i < r && j >= 0 && j < c;
    }

    vector<string> map;

    int r, c;
    int si, sj;
    static constexpr int di[4] = {-1, 0, 1, 0};
    static constexpr int dj[4] = {0, 1, 0, -1};
};

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> map;
    while (getline(file, line)) {
        map.push_back(line);
    }

    MapSolver mapSolver(std::move(map));
    cout << mapSolver.solve() << endl;

    return 0;
}
