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

    pair<int, int> d1[] = {make_pair(1, 1), make_pair(-1, -1)};
    pair<int, int> d2[] = {make_pair(1, -1), make_pair(-1, 1)};
    string xmas = "XMAS";
    int xmasCount = 0;

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < columns - 1; ++j) {
            if (input[i][j] == 'A') {
                int i1 = i + d1[0].first;
                int j1 = j + d1[0].second;
                int i2 = i + d1[1].first;
                int j2 = j + d1[1].second;
                bool diagonal1 = (input[i1][j1] == 'M' && input[i2][j2] == 'S') || (input[i1][j1] == 'S' && input[i2][j2] == 'M');

                i1 = i + d2[0].first;
                j1 = j + d2[0].second;
                i2 = i + d2[1].first;
                j2 = j + d2[1].second;
                bool diagonal2 = (input[i1][j1] == 'M' && input[i2][j2] == 'S') || (input[i1][j1] == 'S' && input[i2][j2] == 'M');

                if (diagonal1 && diagonal2) {
                    ++xmasCount;
                }
            }

        }
    }

    cout << xmasCount << endl;

    return 0;
}
