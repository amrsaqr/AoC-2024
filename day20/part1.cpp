#include <iostream>
#include <fstream>
using namespace std;

class RacetrackSolver {
public:
    explicit RacetrackSolver(vector<string>&& track) : track(std::move(track)), r{(int)this->track.size()}, c{(int)this->track[0].size()} {
    }

    int solve(int minimumSaves) {
        findStartingPosition();

        vector<vector<int>> distance(r, vector<int>(c, 0));
        calculateDistanceFromStart(distance);

        return countCheats(minimumSaves, distance);
    }

private:
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cout << track[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    int countCheats(int minimumSaves, const vector<vector<int>>& distance) {
        int cheats = 0;

        for (int i = si, j = sj; track[i][j] != 'E'; ) {
            if (track[i][j] == 'T') {
                track[i][j] = '.';
            }

            //print();

            cheats += processAdjacentWalls(i, j, minimumSaves, distance);

            for (int d = 0; d < 4; ++d) {
                int ni = i + di[d];
                int nj = j + dj[d];

                if (track[ni][nj] == 'T' || track[ni][nj] == 'E') {
                    i = ni;
                    j = nj;
                    break;
                }
            }
        }

        return cheats;
    }

    int processAdjacentWalls(int i, int j, int minimumSaves, const vector<vector<int>>& distance) {
        int cheats = 0;

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];

            if (track[ni][nj] == '#') {
                for (int dd = 0; dd < 4; ++dd) {
                    int nni = ni + di[dd];
                    int nnj = nj + dj[dd];

                    if (nni >= 0 && nni < r && nnj >= 0 && nnj < c && (track[nni][nnj] == 'T' || track[nni][nnj] == 'E')) {
                        int newDistance = distance[i][j] + 2;
                        int saves = distance[nni][nnj] - newDistance;
                        if (saves >= minimumSaves) {
                            ++cheats;
                        }
                    }
                }
            }
        }

        return cheats;
    }

    void calculateDistanceFromStart(vector<vector<int>>& distance) {
        for (int current = 0, i = si, j = sj; ; ++current) {
            distance[i][j] = current;

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
    cout << solver.solve(100) << endl;

    return 0;
}