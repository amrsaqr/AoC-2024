#include <iostream>
#include <fstream>
#include <sstream>
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
    unordered_map<char, vector<pair<int, int>>> freqs;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (map[i][j] != '.') {
                freqs[map[i][j]].emplace_back(i, j);
            }
        }
    }

    auto inMap = [&r, &c](int i, int j) {
        return i >= 0 && i < r && j >= 0 && j < c;
    };

    int count = 0;
    vector<vector<bool>> vis(r, vector<bool>(c, false));
    for (const auto& freq : freqs) {
        const auto& positions = freq.second;
        for (int ant1 = 0; ant1 < positions.size(); ++ant1) {
            for (int ant2 = ant1 + 1; ant2 < positions.size(); ++ant2) {
                auto position1 = positions[ant1];
                auto position2 = positions[ant2];
                int di = position1.first - position2.first;
                int dj = position1.second - position2.second;

                while (inMap(position1.first, position1.second)) {
                    if (!vis[position1.first][position1.second]) {
                        vis[position1.first][position1.second] = true;
                        ++count;
                    }

                    position1.first += di;
                    position1.second += dj;
                }

                while (inMap(position2.first, position2.second)) {
                    if (!vis[position2.first][position2.second]) {
                        vis[position2.first][position2.second ] = true;
                        ++count;
                    }

                    position2.first -= di;
                    position2.second -= dj;
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}
