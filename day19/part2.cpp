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

        vector<int64_t> dp(len + 1, -1);
        dp[len] = 1;

        return countArrangementsHelper(design, 0, dp);
    }

private:
    int64_t countArrangementsHelper(const string& design, uint s, vector<int64_t>& dp) {
        int64_t& result = dp[s];
        if (result != -1) {
            return result;
        }

        result = 0;

        for (uint length = 1; length <= maximumPatternLength && s < design.length(); ++length, ++s) {
            if (patterns.count(design.substr(s - length + 1, length))) {
                result += countArrangementsHelper(design, s + 1, dp);
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
    int64_t count = 0;
    while (file >> line) {
        count += towelsSolver.countArrangements(line);
    }

    cout << count << endl;

    return 0;
}