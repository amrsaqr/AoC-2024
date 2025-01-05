#include <iostream>
#include <fstream>
using namespace std;

class RacetrackSolver {
public:
    explicit RacetrackSolver(vector<string>&& track) : track(std::move(track)), r{(int)this->track.size()}, c{(int)this->track[0].size()} {
    }

    int solve(int minimumSaves, int maxPicos) {
        findStartingPosition();

        vector<pair<int, int>> path;
        buildPath(path);

        return countCheats(minimumSaves, maxPicos, path);
    }

private:
    static int countCheats(int minimumSaves, int maxPicos, const vector<pair<int, int>>& path) {
        int cheats = 0;

        for (int i = 0; i < path.size(); ++i) {
            for (int j = i + 1; j < path.size(); ++j) {
                const auto& p1 = path[i];
                const auto& p2 = path[j];
                int ijDist = hammingDistance(p1, p2);
                if (ijDist <= maxPicos) {
                    int newDistance = i + ijDist;
                    int saves = j - newDistance;
                    if (saves >= minimumSaves) {
                        ++cheats;
                    }
                }
            }
        }

        return cheats;
    }

    static int hammingDistance(const pair<int, int>& p1, const pair<int, int>& p2) {
        return abs(p1.first - p2.first) + abs(p1.second - p2.second);
    }

    void buildPath(vector<pair<int, int>>& path) {
        for (int i = si, j = sj; ; ) {
            path.emplace_back(i, j);

            if (track[i][j] == 'E') {
                break;
            }

            if (track[i][j] == '.') {
                track[i][j] = 'T';
            }

            for (int d = 0; d < 4; ++d) {
                int ni = i + di[d];
                int nj = j + dj[d];

                if (track[ni][nj] == '.' || track[ni][nj] == 'E') {
                    i = ni;
                    j = nj;
                    break;
                }
            }
        }
    }

    void findStartingPosition() {
        bool found = false;
        for (int i = 0; i < r && !found; ++i) {
            for (int j = 0; j < c && !found; ++j) {
                if (track[i][j] == 'S') {
                    si = i;
                    sj = j;
                    found = true;
                }
            }
        }
    }

    vector<string> track;
    int r;
    int c;
    int si{-1};
    int sj{-1};
    static constexpr int di[4]{0, 0, 1, -1};
    static constexpr int dj[4]{1, -1, 0, 0};
};

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> track;
    while (getline(file, line)) {
        track.push_back(line);
    }

    RacetrackSolver solver(std::move(track));
    cout << solver.solve(100, 20) << endl;

    return 0;
}