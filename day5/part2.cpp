#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
using namespace std;

int main() {
    ifstream file("input.txt");

    string line;
    char ch;
    int x, y;
    unordered_map<int, unordered_set<int>> rules;

    while (getline(file, line) && !line.empty()) {
        istringstream iss(line);
        iss >> x >> ch >> y;
        rules[x].insert(y);
    }

    int sum = 0;
    while (getline(file, line)) {
        vector<int> pages;
        istringstream iss(line);
        for (bool first = true; (first || iss >> ch) && iss >> x; first = false) {
            pages.push_back(x);
        }

        int pagesCount = (int)pages.size();
        vector<int> counts(pagesCount, 0);
        for (int i = 0; i < pagesCount; ++i) {
            for (int j = 0; j < pagesCount; ++j) {
                if (i != j) {
                    if (rules[pages[i]].count(pages[j]) != 0) {
                        ++counts[i];
                    }
                }
            }
        }

        bool sorted = true;
        for (int i = 1; i < pagesCount; ++i) {
            if (counts[i] > counts[i - 1]) {
                sorted = false;
                break;
            }
        }

        if (!sorted) {
            int targetCount = pagesCount / 2;
            for (int i = 0; i < pagesCount; ++i) {
                if (counts[i] == targetCount) {
                    sum += pages[i];
                    break;
                }
            }
        }
    }

    cout << sum << endl;

    return 0;
}
