#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

class TowelsSolver {
public:
    explicit TowelsSolver(unordered_set<string>&& patterns) : patterns{std::move(patterns)} {
        calculateMaximumPatternLength();
    }

    int64_t countArrangements(const string& design) {
        uint len = design.length();

        vector<vector<bool>> isPattern(len, vector<bool>(len, false));
        setPatternsInDesign(design, isPattern);

        vector<vector<int64_t>> dp(len, vector<int64_t>(len, -1));
        return countArrangementsHelper(design, 0, len - 1, isPattern, dp);
    }

private:
    int64_t countArrangementsHelper(const string& design, uint s, uint e, const vector<vector<bool>>& isPattern, vector<vector<int64_t>>& dp) {
        if (s == design.length()) {
            return 1;
        }

        int64_t& result = dp[s][e];
        if (result != -1) {
            return result;
        }

        result = 0;

        for (uint i = s; i <= e && i - s + 1 <= maximumPatternLength; ++i) {
            if (isPattern[s][i]) {
                result += countArrangementsHelper(design, i + 1, e, isPattern, dp);
            }
        }

        return result;
    }

    void setPatternsInDesign(const string &design, vector<vector<bool>>& isPattern) {
        uint len = design.length();
        for (uint i = 0; i < len; ++i) {
            for (uint j = i; j < len && j - i + 1 <= maximumPatternLength; ++j) {
                if (patterns.count(design.substr(i, j - i + 1))) {
                    isPattern[i][j] = true;
                }
            }
        }
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
    int64_t count = 0;
    while (file >> line) {
        count += towelsSolver.countArrangements(line);
    }

    cout << count << endl;

    return 0;
}