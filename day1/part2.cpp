#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    int x;
    int y;
    vector<int> left;
    unordered_map<int, int> right;

    while (file >> x >> y) {
        left.push_back(x);
        ++right[y];
    }

    int score = 0;
    for (int num : left) {
        score += num * right[num];
    }

    cout << score << endl;

    return 0;
}