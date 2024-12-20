#include <iostream>
#include <fstream>
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
private:
    int gpsSum() {
        int sum = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (map[i][j] == 'O') {
                    sum += (i * 100 + j);
                }
            }
        }
        return sum;
    }

    void executeMoves(const vector<char>& moves) {
        for (char move : moves) {
            int dir = getDir(move);

            int ei = si + di[dir];
            int ej = sj + dj[dir];
            while (map[ei][ej] == 'O') {
                ei += di[dir];
                ej += dj[dir];
            }

            if (map[ei][ej] == '.') {
                shift(ei, ej, (dir + 2) % 4);
            }

//            cout << "Move " << move << ":" << endl;
//            printMap();
        }
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

    void shift(int ei, int ej, int dir) {
        int i = ei;
        int j = ej;
        while (i != si || j != sj) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            map[i][j] = map[ni][nj];
            i = ni;
            j = nj;
        }

        map[i][j] = '.';
        si = i - di[dir];
        sj = j - dj[dir];
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

    char ch;
    vector<char> moves;
    while (file >> ch) {
        moves.push_back(ch);
    }

    WarehouseSolver solver(std::move(map));
    cout << solver.solve(moves) << endl;

    return 0;
}