#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int base;
    int limit;
} Segment;

Segment segmentTable[5];

void createSegmentTable() {
    int bases[] = {1400, 6300, 4300, 3200, 4700};
    int limits[] = {1000, 2000, 500, 400, 1100};
    for (int i = 0; i < 5; i++) {
        segmentTable[i].base = bases[i];
        segmentTable[i].limit = limits[i];
    }
}

int translateAddress(int segmentNum, int offset) {
    if (segmentNum < 0 || segmentNum > 4) {
        printf("Invalid segment number\n");
        return -1;
    }
    if (offset >= segmentTable[segmentNum].limit) {
        printf("Offset exceeds segment limit\n");
        return -1;
    }
    return segmentTable[segmentNum].base + offset;
}

int main() {
    createSegmentTable();
    
    int testCases[][2] = {{2, 53}, {3, 852}, {0, 1222}};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTestCases; i++) {
        int segmentNum = testCases[i][0];
        int offset = testCases[i][1];
        int physicalAddress = translateAddress(segmentNum, offset);
        if (physicalAddress != -1) {
            printf("Logical Address: Segment %d, Offset %d\n", segmentNum, offset);
            printf("Physical Address: %d\n\n", physicalAddress);
        }
    }
    
    return 0;
}
