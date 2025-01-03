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

        vector<int> dp(len + 1, -1);
        dp[len] = 1;

        int result = isDesignPossibleHelper(design, 0, dp);
        return result == 1;
    }

private:
    int isDesignPossibleHelper(const string& design, uint s, vector<int>& dp) {
        int& result = dp[s];
        if (result != -1) {
            return result;
        }

        result = 0;

        for (uint length = 1; length <= maximumPatternLength && s < design.length(); ++length, ++s) {
            if (patterns.count(design.substr(s - length + 1, length)) && isDesignPossibleHelper(design, s + 1, dp)) {
                result = 1;
                break;
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