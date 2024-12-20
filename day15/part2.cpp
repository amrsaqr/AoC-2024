#include <iostream>
#include <fstream>
#include <set>
using namespace std;

class WarehouseSolver {
public:
    explicit WarehouseSolver(vector<string>&& map) : map(std::move(map)), r{this->map.size()}, c{this->map[0].size()} {
    }

    int solve(const vector<char>& moves) {
        findStartingPoint();
        executeMoves(moves);
        return gpsSum();
    }

    void printMap() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
private:
    int gpsSum() {
        int sum = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (map[i][j] == '[') {
                    sum += (i * 100 + j);
                }
            }
        }
        return sum;
    }

    void executeMoves(const vector<char>& moves) {
        for (char move : moves) {
            int dir = getDir(move);

            if (dir % 2) {
                moveVertically(dir);
            } else {
                moveHorizontally(dir);
            }

//            cout << "Move " << move << ":" << endl;
//            printMap();
        }
    }

    void moveVertically(int dir) {
        vector<set<pair<int, int>>> rows{{make_pair(si, sj)}};
        bool shouldShift = true;
        while (shouldShift) {
            bool wallBlockFound = false;

            set<pair<int, int>> nextRow;
            for (const auto& item : rows.back()) {
                int ni = item.first + di[dir];
                int nj = item.second + dj[dir];
                if (map[ni][nj] == '#') {
                    wallBlockFound = true;
                    break;
                } else if (map[ni][nj] == '[') {
                    nextRow.emplace(ni, nj);
                    nextRow.emplace(ni, nj + 1);
                } else if (map[ni][nj] == ']') {
                    nextRow.emplace(ni, nj);
                    nextRow.emplace(ni, nj - 1);
                }
            }

            if (wallBlockFound) {
                shouldShift = false;
            }

            if (nextRow.empty()) {
                break;
            } else {
                rows.emplace_back(nextRow);
            }
        }

        if (shouldShift) {
            shiftVertically(rows, dir);
            map[si][sj] = '.';
            si += di[dir];
            sj += dj[dir];
        }
    }

    void shiftVertically(const vector<set<pair<int, int>>>& rows, int dir) {
        for (auto it = rows.rbegin(); it != rows.rend(); ++it) {
            for (const auto& item : *it) {
                int ni = item.first + di[dir];
                int nj = item.second + dj[dir];
                map[ni][nj] = map[item.first][item.second];
                map[item.first][item.second] = '.';
            }
        }
    }

    void moveHorizontally(int dir) {
        int ei = si + di[dir];
        int ej = sj + dj[dir];
        while (map[ei][ej] == '[' || map[ei][ej] == ']') {
            ei += di[dir];
            ej += dj[dir];
        }

        if (map[ei][ej] == '.') {
            shiftHorizontally(ei, ej, (dir + 2) % 4);
            map[si][sj] = '.';
            si += di[dir];
            sj += dj[dir];
        }
    }

    void shiftHorizontally(int ei, int ej, int dir) {
        int i = ei;
        int j = ej;
        while (i != si || j != sj) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            map[i][j] = map[ni][nj];
            i = ni;
            j = nj;
        }
    }

    void findStartingPoint() {
        bool found = false;
        for (int i = 0; i < r && !found; ++i) {
            for (int j = 0; j < c && !found; ++j) {
                if (map[i][j] == '@') {
                    si = i;
                    sj = j;
                    found = true;
                }
            }
        }
    }

    vector<string> map;
    const size_t r;
    const size_t c;
    int si{-1};
    int sj{-1};
    static constexpr int getDir(char ch) {
        switch (ch) {
            case '>':
                return 0;
            case 'v':
                return 1;
            case '<':
                return 2;
            case '^':
                return 3;
            default:
                return -1;
        }
    }
    static constexpr int di[4]{0, 1, 0, -1};
    static constexpr int dj[4]{1, 0, -1, 0};
};

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> map;
    while (true) {
        file >> line;
        map.push_back(line);

        if (map.size() > 1 && all_of(line.begin(), line.end(), [](char ch){ return ch == '#';})) {
            break;
        }
    }

    vector<string> scaledMap(map.size(), string(map[0].size() * 2, ' '));
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            int sj = j * 2;
            switch (map[i][j]) {
                case '@':
                    scaledMap[i][sj] = '@';
                    scaledMap[i][sj + 1] = '.';
                    break;
                case '.':
                    scaledMap[i][sj] = '.';
                    scaledMap[i][sj + 1] = '.';
                    break;
                case '#':
                    scaledMap[i][sj] = '#';
                    scaledMap[i][sj + 1] = '#';
                    break;
                case 'O':
                    scaledMap[i][sj] = '[';
                    scaledMap[i][sj + 1] = ']';
                    break;
                default:
                    break;
            }
        }
    }

    char ch;
    vector<char> moves;
    while (file >> ch) {
        moves.push_back(ch);
    }

    WarehouseSolver solver(std::move(scaledMap));
    cout << solver.solve(moves) << endl;

    return 0;
}