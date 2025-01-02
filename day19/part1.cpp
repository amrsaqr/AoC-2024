#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

class TowelsSolver {
public:
    explicit TowelsSolver(unordered_set<string>&& patterns) : patterns{std::move(patterns)} {
        calculateMaximumPatternLength();
    }

    bool isDesignPossible(const string& design) {
        uint len = design.length();
        vector<vector<int>> dp(len, vector<int>(len, -1));
        int result = isDesignPossibleHelper(design, 0, len - 1, dp);
        return result == 1;
    }

private:
    int isDesignPossibleHelper(const string& design, uint s, uint e, vector<vector<int>>& dp) {
        int& result = dp[s][e];
        if (result != -1) {
            return result;
        }

        if (s == e) {
            result = patterns.count(design.substr(s, 1)) ? 1 : 0;
        } else if (e - s + 1 <= maximumPatternLength && patterns.count(design.substr(s, e - s + 1))) {
            result = 1;
        } else {
            result = 0;
            uint subLength = e - s + 1;
            for (uint leftLength = 1, rightLength = subLength - 1; rightLength; ++leftLength, --rightLength) {
                if (isDesignPossibleHelper(design, s, s + leftLength - 1, dp) && isDesignPossibleHelper(design, s + leftLength, s + leftLength + rightLength - 1, dp)) {
                    result = 1;
                    break;
                }
            }
        }

        return result;
    }

    void calculateMaximumPatternLength() {
        for (const auto& pattern : patterns) {
            maximumPatternLength = max(maximumPatternLength, pattern.length());
        }
    }

    unordered_set<string> patterns;
    size_t maximumPatternLength{0};
};

int main() {
    ifstream file("input.txt");

    string line;
    getline(file, line);

    const string delimiter = ", ";
    unordered_set<string> patterns;
    for (size_t start = 0; ; ) {
        size_t end = line.find(delimiter, start);
        patterns.emplace(line.substr(start, end - start));

        if (end == string::npos) {
            break;
        }

        start = end + 2;
    }

    TowelsSolver towelsSolver(std::move(patterns));
    uint count = 0;
    while (file >> line) {
        if (towelsSolver.isDesignPossible(line)) {
            ++count;
        }
    }

    cout << count << endl;

    return 0;
}