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
        int score = 0;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (map[i][j] == '0') {
                    vector<vector<bool>> vis(r, vector<bool>(c, false));
                    dfs(i, j, vis, score);
                }
            }
        }

        return score;
    }

    bool inMap(int i, int j) const {
        return i >= 0 && i < r && j >= 0 && j < c;
    }

    void dfs(int i, int j, vector<vector<bool>>& vis, int& score) {
        vis[i][j] = true;

        if (map[i][j] == '9') {
            ++score;
            return;
        }

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];

            if (inMap(ni, nj) && !vis[ni][nj] && map[ni][nj] - map[i][j] == 1) {
                dfs(ni, nj, vis, score);
            }
        }
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
