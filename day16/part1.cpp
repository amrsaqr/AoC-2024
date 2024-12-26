#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct ScoredOrientedTile {
    ScoredOrientedTile(int i, int j, int dir, int score) : i{i}, j{j}, dir{dir}, score{score} {
    }

    bool operator<(const ScoredOrientedTile& other) const {
        return score > other.score;
    }

    int i, j, dir, score;
};

class MazeSolver {
public:
    explicit MazeSolver(vector<string>&& maze) : maze(std::move(maze)) {
    }

    int solve() {
        int r = (int)maze.size();
        int c = (int)maze[0].size();
        int bestScore = -1;
        priority_queue<ScoredOrientedTile> unvisited;
        set<tuple<int, int, int>> visited;

        unvisited.emplace(r - 2, 1, 0, 0);
        while (!unvisited.empty()) {
            auto current = unvisited.top();
            unvisited.pop();

            if (current.i == 1 && current.j == c - 2) {
                bestScore = current.score;
                break;
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

                unvisited.emplace(ni, nj, d, current.score + (current.dir == d ? 1 : 1001));
            }
        }

        return bestScore;
    }

private:
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