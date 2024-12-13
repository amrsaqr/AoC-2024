#include <iostream>
#include <fstream>
using namespace std;

class TrailheadsSolver {
public:
    explicit TrailheadsSolver(vector<string>&& map) : map(std::move(map)) {
        r = (int)this->map.size();
        c = (int)this->map[0].size();
    }

    int solve() {
        vector<vector<int>> counts(r, vector<int>(c, 0));
        for (int h = '9'; h >= '0'; --h) {
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    if (map[i][j] == h) {
                        if (h == '9') {
                            counts[i][j] = 1;
                        } else {
                            for (int d = 0; d < 4; ++d) {
                                int ni = i + di[d];
                                int nj = j + dj[d];

                                if (inMap(ni, nj) && map[ni][nj] - map[i][j] == 1) {
                                    counts[i][j] += counts[ni][nj];
                                }
                            }
                        }
                    }
                }
            }
        }

        int score = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (map[i][j] == '0') {
                    score += counts[i][j];
                }
            }
        }

        return score;
    }

    bool inMap(int i, int j) const {
        return i >= 0 && i < r && j >= 0 && j < c;
    }

private:
    vector<string> map;
    int r;
    int c;
    static constexpr int di[4] {1, -1, 0, 0};
    static constexpr int dj[4] {0, 0, 1, -1};
};

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> map;
    while (getline(file, line)) {
        map.push_back(line);
    }

    TrailheadsSolver solver(std::move(map));
    cout << solver.solve() << endl;

    return 0;
}
