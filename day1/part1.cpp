#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    int x;
    int y;
    vector<int> left;
    vector<int> right;

    while (file >> x >> y) {
        left.push_back(x);
        right.push_back(y);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int distance = 0;
    for (int i = 0; i < left.size(); ++i) {
        distance += abs(left[i] - right[i]);
    }

    cout << distance << endl;

    return 0;
}
