#include <iostream>
#include <fstream>
#include <set>
#include <map>
using namespace std;

struct ScoredOrientedTile {
    ScoredOrientedTile(int i, int j, int dir, int score) : i{i}, j{j}, dir{dir}, score{score} {
    }

    bool operator<(const ScoredOrientedTile& other) const {
        return score > other.score;
    }

    int i, j, dir, score;
};

struct TileScores {
    TileScores() = default;

    void checkAddScoreAndParent(int score, int dir) {
        int& bestScore = bestScores[dir];
        if (bestScore == -1 || score < bestScore) {
            bestScore = score;
        }
    }

    bool hasValue(int dir) const {
        return bestScores[dir] != -1;
    }

    int value(int dir) const {
        return bestScores[dir];
    }

    int bestScores[4]{-1, -1, -1, -1};
};

class MazeSolver {
public:
    explicit MazeSolver(vector<string>&& maze) : maze(std::move(maze)) {
    }

    int solve() {
        int r = (int)maze.size();
        int c = (int)maze[0].size();
        int bestScore = numeric_limits<int>::max();
        int reachedEndCount = 0;
        priority_queue<ScoredOrientedTile> unvisited;
        set<tuple<int, int, int>> visited;
        map<pair<int, int>, TileScores> bestScores;

        bestScores[{r - 2, 1}].checkAddScoreAndParent(0, 0);
        unvisited.emplace(r - 2, 1, 0, 0);
        while (!unvisited.empty()) {
            auto current = unvisited.top();
            unvisited.pop();

            if (current.i == 1 && current.j == c - 2) {
                ++reachedEndCount;
                bestScore = min(bestScore, current.score);

                if (reachedEndCount == 2) {
                    break;
                }
            }

            if (visited.count({current.i, current.j, current.dir})) {
                continue;
            }
            visited.emplace(current.i, current.j, current.dir);

            for (int d = 0; d < 4; ++d) {
                if (current.dir == (d + 2) % 4) {
                    continue;
                }

                int ni = current.i + di[d];
                int nj = current.j + dj[d];

                if (maze[ni][nj] == '#') {
                    continue;
                }

                int ns = current.score + (current.dir == d ? 1 : 1001);

                bestScores[{ni, nj}].checkAddScoreAndParent(ns, d);
                unvisited.emplace(ni, nj, d, ns);
            }
        }

        set<pair<int, int>> vis;
        int count = 0;
        dfsCount(1, c - 2, bestScore, count, vis, bestScores);

        return count;
    }

private:
    bool dfsCount(int i, int j, int bestScore, int& count, set<pair<int, int>>& vis, const map<pair<int, int>, TileScores>& bestScores) {
        pair<int, int> key{i, j};
        auto it = bestScores.find(key);
        bool validToS = false;

        for (int d = 0; d < 4; ++d) {
            if (it->second.hasValue(d)) {
                int scoreAtD = it->second.value(d);
                if (scoreAtD != bestScore && scoreAtD != bestScore - 1000) {
                    continue;
                }

                if (maze[i][j] == 'S') {
                    validToS = true;
                } else {
                    int dd = (d + 2) % 4;
                    int ni = i + di[dd];
                    int nj = j + dj[dd];

                    if (dfsCount(ni, nj, scoreAtD - 1, count, vis, bestScores) || dfsCount(ni, nj, scoreAtD - 1001, count, vis, bestScores)) {
                        validToS = true;
                    }
                }
            }
        }

        if (validToS && !vis.count(key)) {
            ++count;
            vis.insert(key);
        }

        return validToS;
    }

    vector<string> maze;
    static constexpr int di[4]{0, 1, 0, -1};
    static constexpr int dj[4]{1, 0, -1, 0};
};

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> maze;
    while (getline(file, line)) {
        maze.push_back(line);
    }

    MazeSolver solver(std::move(maze));
    cout << solver.solve() << endl;

    return 0;
}