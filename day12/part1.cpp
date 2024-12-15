#include <iostream>
#include <fstream>
using namespace std;

class GardenSolver {
public:
    explicit GardenSolver(vector<string>&& map) : map(std::move(map)), r{this->map.size()}, c{this->map[0].size()}, vis(r, vector<bool>(c, false)) {
    }

    int solve() {
        int price = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (!vis[i][j]) {
                    int area = 0;
                    int perimeter = 0;
                    floodfill(i, j, map[i][j], area, perimeter);
                    price += area * perimeter;
                }
            }
        }

        return price;
    }

    void floodfill(int i, int j, const char plant, int& area, int& perimeter) {
        vis[i][j] = true;
        ++area;

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];

            if (!inMap(ni, nj) || map[ni][nj] != plant) {
                ++perimeter;
            } else if (!vis[ni][nj]) {
                floodfill(ni, nj, plant, area, perimeter);
            }
        }
    }

    bool inMap(int i, int j) {
        return i >= 0 && i < r && j >= 0 && j < c;
    }
private:
    const vector<string> map;
    const size_t r;
    const size_t c;
    vector<vector<bool>> vis;
    static constexpr int di[4] = {0, 0, 1, -1};
    static constexpr int dj[4] = {1, -1, 0, 0};
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
