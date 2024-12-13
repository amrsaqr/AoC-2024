#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    string diskMap;
    getline(file, diskMap);

    vector<int> blocks;
    for (int dmi = 0, id = 0; dmi < diskMap.size(); ++dmi) {
        int length = diskMap[dmi] - '0';
        if (dmi % 2) {
            for (int i = 0; i < length; ++i) {
                blocks.push_back(-1);
            }
        } else {
            for (int i = 0; i < length; ++i) {
                blocks.push_back(id);
            }
            ++id;
        }
    }

    int freeBlock = 0;
    auto advanceFreeBlockIndex = [&blocks, &freeBlock]() {
        while (++freeBlock < blocks.size() && blocks[freeBlock] != -1);
    };

    int fileBlock = (int)blocks.size() - 1;
    auto retreatFileBlockIndex = [&blocks, &fileBlock]() {
        while (--fileBlock >= 0 && blocks[fileBlock] == -1);
    };

    advanceFreeBlockIndex();

    while (freeBlock < fileBlock) {
        blocks[freeBlock] = blocks[fileBlock];
        blocks[fileBlock] = -1;

        advanceFreeBlockIndex();
        retreatFileBlockIndex();
    }

    int64_t checksum = 0;
    for (int i = 0; i < blocks.size() && blocks[i] != -1; ++i) {
        checksum += (i * blocks[i]);
    }

    cout << checksum << endl;

    return 0;
}
