#include <iostream>
#include <fstream>
using namespace std;

class GardenSolver {
public:
    explicit GardenSolver(vector<string>&& map) : map(std::move(map)), r{this->map.size()}, c{this->map[0].size()}, vis(r, vector<bool>(c, false)), fences(r, vector<vector<bool>>(c, vector<bool>(4, false))) {
    }

    int solve() {
        int price = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (!vis[i][j]) {
                    int area = 0;
                    int sides = 0;
                    floodfill(i, j, map[i][j], area, sides);
                    price += area * sides;
                }
            }
        }

        return price;
    }

    void floodfill(int i, int j, const char plant, int& area, int& sides) {
        vis[i][j] = true;
        ++area;

        for (int d = 0; d < 4; ++d) {
            if (isEdgeForDir(i, j, d, plant) && !fences[i][j][d]) {
                ++sides;
                fences[i][j][d] = true;

                int d1 = (d + 1) % 4;
                for (int si = i + di[d1], sj = j + dj[d1]; isEdgeForDir(si, sj, d, plant) && inMap(si, sj) && map[si][sj] == plant; si += di[d1], sj += dj[d1]) {
                    fences[si][sj][d] = true;
                }

                int d2 = (d + 3) % 4;
                for (int si = i + di[d2], sj = j + dj[d2]; isEdgeForDir(si, sj, d, plant) && inMap(si, sj) && map[si][sj] == plant; si += di[d2], sj += dj[d2]) {
                    fences[si][sj][d] = true;
                }
            }
        }

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];

            if (inMap(ni, nj) && map[ni][nj] == plant && !vis[ni][nj]) {
                floodfill(ni, nj, plant, area, sides);
            }
        }
    }

    bool inMap(int i, int j) {
        return i >= 0 && i < r && j >= 0 && j < c;
    }

    bool isEdgeForDir(int i, int j, int d, char plant) {
        int fi = i + di[d];
        int fj = j + dj[d];
        return !inMap(fi, fj) || map[fi][fj] != plant;
    }
private:
    const vector<string> map;
    const size_t r;
    const size_t c;
    vector<vector<bool>> vis;
    vector<vector<vector<bool>>> fences;
    static constexpr int di[4] = {0, 1, 0, -1};
    static constexpr int dj[4] = {1, 0, -1, 0};
};

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> map;
    while (getline(file, line)) {
        map.push_back(line);
    }

    GardenSolver solver(std::move(map));
    cout << solver.solve() << endl;

    return 0;
}
