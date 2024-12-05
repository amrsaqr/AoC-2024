#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int main() {
    ifstream file("input.txt");

    regex re(R"(mul\((\d+),(\d+)\)|do\(\)|(don't\(\)))");
    bool enabled = true;
    string line;
    int sum = 0;

    while (getline(file, line)) {
        auto begin = sregex_iterator(line.begin(), line.end(), re);
        auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            const smatch& match = *it;

            if (match[0] == "do()") {
                enabled = true;
            } else if (match[0] == "don't()") {
                enabled = false;
            } else if (enabled) {
                int x = stoi(match[1]);
                int y = stoi(match[2]);
                sum += x * y;
            }
        }
    }

    cout << sum << endl;

    return 0;
}
