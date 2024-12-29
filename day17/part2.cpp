#include <iostream>
#include <fstream>
#include <set>
using namespace std;

uint equation(uint64_t a) {
    uint b1 = (a % 8) ^ 5;
    uint b2 = b1 ^ 6;
    uint64_t c = a >> b1;
    uint b3 = b2 ^ c;
    return b3 % 8;
}

bool doesAProduceProgram(uint64_t a, const vector<uint64_t>& program) {
    uint matchesCount = 0;

    for (uint i = 0; a; ++i, a /= 8) {
        if (equation(a) != program[i]) {
            return false;
        }

        ++matchesCount;
    }

    return matchesCount == program.size();
}

int main() {
    ifstream file("input.txt");

    string skip, program;
    getline(file, skip);
    getline(file, skip);
    getline(file, skip);
    file >> skip >> program;

    // the number of outputs of the self printing program
    const uint outputSize = program.size() / 2 + 1;

    // store program in array of integers
    vector<uint64_t> selfPrintingProgram;
    for (uint i = 0; i < program.size(); i += 2) {
        selfPrintingProgram.push_back(program[i] - '0');
    }

    // initialize the seed for generating A values
    uint tenBitsLimit = (1 << 10) - 1;
    vector<vector<uint64_t>> values(outputSize);
    for (uint n = 0; n < tenBitsLimit; ++n) {
        if (equation(n) == selfPrintingProgram[0]) {
            values[0].push_back(n);
        }
    }

    // a loop for generating A values, with each iteration adding 3 more bits to the mix
    const uint mask = 0x7f;
    for (uint64_t i = 1, shift = 3; i < outputSize; ++i, shift += 3) {
        const vector<uint64_t>& prev = values[i - 1];

        for (uint64_t v : prev) {
            uint64_t n = (v >> shift) & mask;

            for (uint x = (i == 15 ? 1 : 0); x < 8; ++x) {
                uint64_t test = (x << 7) | n;
                if (equation(test) == selfPrintingProgram[i]) {
                    values[i].push_back((test << shift) | v);
                }
            }
        }
    }

    // store all generated values in a unique set
    set<uint64_t> as;
    for (const auto& arr : values) {
        as.insert(arr.begin(), arr.end());
    }

    // find the first(lowest) value that causes program to self-print
    for (auto a : as) {
        if (doesAProduceProgram(a, selfPrintingProgram)) {
            cout << a << endl;
            break;
        }
    }

    return 0;
}