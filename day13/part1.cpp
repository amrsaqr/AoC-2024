#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    string word;
    char ch;
    int ax, ay;
    int bx, by;
    int px, py;

    int total = 0;
    while (file >> word >> word >> ch >> ch >> ax >> ch >> ch >> ch >> ay) {
        file >> word >> word >> ch >> ch >> bx >> ch >> ch >> ch >> by;
        file >> word >> ch >> ch >> px >> ch >> ch >> ch >> py;

        int tokens = -1;
        for (int as = 0; as <= 100 && tokens == -1; ++as) {
            for (int bs = 0; bs <= 100 && tokens == -1; ++bs) {
                int x = (ax * as) + (bx * bs);
                int y = (ay * as) + (by * bs);
                if (x == px && y == py) {
                    tokens = 3 * as + bs;
                }
            }
        }

        if (tokens != -1) {
            total += tokens;
        }
    }

    cout << total << endl;

    return 0;
}