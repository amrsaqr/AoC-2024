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

        bool valid = true;
        for (int i = 0; i < pages.size() && valid; ++i) {
            for (int j = i + 1; j < pages.size() && valid; ++j) {
                if (rules[pages[i]].count(pages[j]) == 0) {
                    valid = false;
                }
            }
        }

        if (valid) {
            sum += pages[pages.size() / 2];
        }
    }

    cout << sum << endl;

    return 0;
}
