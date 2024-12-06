#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> input;

    while (getline(file, line)) {
        input.push_back(line);
    }

    int rows = (int)input.size();
    int columns = (int)input[0].size();
    vector<vector<int>> links(rows, vector<int>(columns, 0));

    int di[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dj[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    string xmas = "XMAS";
    int xmasCount = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (input[i][j] == 'X') {
                for (int d = 0; d < 8; ++d) {
                    int matches = 0;
                    for (int x = 0, ii = i, jj = j; x < 4 && ii >= 0 && ii < rows && jj >= 0 && jj < columns && input[ii][jj] == xmas[x]; ii += di[d], jj += dj[d], ++x) {
                        ++matches;
                    }

                    if (matches == 4) {
                        ++xmasCount;
                    }
                }
            }
        }
    }

    cout << xmasCount << endl;

    return 0;
}
