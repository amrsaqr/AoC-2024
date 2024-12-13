#include <iostream>
#include <fstream>
#include <set>
using namespace std;

class Segment {
public:
    Segment(int startingBlockPosition, int id, int blocksCount) : startingBlockPosition{startingBlockPosition}, id{id}, blocksCount{blocksCount} {
    }

    bool operator==(const Segment& other) const {
        return startingBlockPosition == other.startingBlockPosition;
    }

    bool operator<(const Segment& other) const {
        return startingBlockPosition < other.startingBlockPosition;
    }

    int64_t checksum() const {
        int64_t result = 0;
        for (int i = startingBlockPosition; i < startingBlockPosition + blocksCount; ++i) {
            result += (i * id);
        }
        return result;
    }

    int startingBlockPosition;
    int id;
    int blocksCount;
};

int main() {
    ifstream file("input.txt");

    string diskMap;
    getline(file, diskMap);

    int currentBlockPosition = 0;
    vector<Segment> files;
    set<Segment> freeSegments[9];
    for (int dmi = 0, id = 0; dmi < diskMap.size(); ++dmi) {
        int length = diskMap[dmi] - '0';

        if (dmi % 2) {
            if (length) {
                freeSegments[length - 1].emplace(currentBlockPosition, -1, length);
            }
        } else {
            files.emplace_back(currentBlockPosition, id++, length);
        }

        currentBlockPosition += length;
    }

    for (auto rit = files.rbegin(); rit != files.rend(); ++rit) {
        Segment& fileSegment = *rit;

        const Segment* earliestFittingFreeSegment = nullptr;
        int earliestBlockPosition = -1;
        for (int length = fileSegment.blocksCount - 1; length < 9; ++length) {
            if (!freeSegments[length].empty()) {
                auto freeSegmentIt = freeSegments[length].cbegin();
                if (freeSegmentIt->startingBlockPosition < fileSegment.startingBlockPosition &&
                (earliestBlockPosition == -1 || freeSegmentIt->startingBlockPosition < earliestBlockPosition)) {
                    earliestFittingFreeSegment = &(*freeSegmentIt);
                    earliestBlockPosition = freeSegmentIt->startingBlockPosition;
                }
            }
        }

        if (earliestFittingFreeSegment) {
            fileSegment.startingBlockPosition = earliestFittingFreeSegment->startingBlockPosition;

            int remainingBlocks = earliestFittingFreeSegment->blocksCount - fileSegment.blocksCount;
            if (remainingBlocks > 0) {
                freeSegments[remainingBlocks - 1].emplace(fileSegment.startingBlockPosition + fileSegment.blocksCount, -1, remainingBlocks);
            }

            freeSegments[earliestFittingFreeSegment->blocksCount - 1].erase(*earliestFittingFreeSegment);
        }
    }

    int64_t checksum = 0;
    for (const auto& fileSegment : files) {
        checksum += fileSegment.checksum();
    }

    cout << checksum << endl;

    return 0;
}
