#include <iostream>
#include <fstream>
using namespace std;

bool prepareDivision(int64_t& numerator, int64_t& denominator) {
    if ((numerator >= 0 && denominator > 0) || (numerator <= 0 && denominator < 0)) {
        if (numerator <= 0) {
            numerator *= -1;
            denominator *= -1;
        }
        return numerator % denominator == 0;
    }
    return false;
}

bool solve(int64_t x, int64_t y, int64_t ax, int64_t bx, int64_t ay, int64_t by, int64_t& a, int64_t& b) {
    int64_t numerator = ax * y - ay * x;
    int64_t denominator = ay * -bx + ax * by;
    if (prepareDivision(numerator, denominator)) {
        b = numerator / denominator;
        numerator = x - bx * b;
        denominator = ax;
        if (prepareDivision(numerator, denominator)) {
            a = numerator / denominator;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream file("input.txt");

    string word;
    char ch;
    int64_t ax, ay;
    int64_t bx, by;
    int64_t px, py;

    int64_t total = 0;
    while (file >> word >> word >> ch >> ch >> ax >> ch >> ch >> ch >> ay) {
        file >> word >> word >> ch >> ch >> bx >> ch >> ch >> ch >> by;
        file >> word >> ch >> ch >> px >> ch >> ch >> ch >> py;

        px += 10000000000000;
        py += 10000000000000;

        int64_t a, b;
        if (solve(px, py, ax, bx, ay, by, a, b)) {
            total += (3 * a + b);
        }
    }

    cout << total << endl;

    return 0;
}
