#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int reqId;
    int arrtstamp;
    int cyl;
    int add;
    int prid;
} DSA;

void FCFS(DSA reqs[], int n, int start) {
    int currpos = start;
    int total_dist = 0;

    printf("\nFCFS Disk Scheduling:\n");
    printf("Move from %d to %d\n", currpos, reqs[0].cyl);
    
    for (int i = 0; i < n; i++) {
        int dist = abs(currpos - reqs[i].cyl);
        total_dist += dist;
        currpos = reqs[i].cyl;
        printf("Move from %d to %d with Seek %d (Request ID: %d, Process ID: %d)\n",
               currpos, reqs[i].cyl, dist, reqs[i].reqId, reqs[i].prid);
    }

    printf("\nTotal Seek Time (FCFS): %d\n", total_dist);
    float avg = (float)total_dist / n;
    printf("Average Seek Time (FCFS): %f\n", avg);
}

void SSTF(DSA reqs[], int n, int start) {
    int currpos = start;
    int total_dist = 0;
    int served[n];
    for (int i = 0; i < n; i++) served[i] = 0;

    printf("\nSSTF Disk Scheduling:\n");
    
    for (int count = 0; count < n; count++) {
        int clstIdx = -1;
        int closest_dist = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!served[i]) {
                int dist = abs(currpos - reqs[i].cyl);
                if (dist < closest_dist) {
                    closest_dist = dist;
                    clstIdx = i;
                }
            }
        }

        if (clstIdx != -1) {
            total_dist += closest_dist;
            printf("Move from %d to %d with Seek %d (Request ID: %d, Process ID: %d)\n",
                   currpos, reqs[clstIdx].cyl, closest_dist, 
                   reqs[clstIdx].reqId, reqs[clstIdx].prid);
            currpos = reqs[clstIdx].cyl;
            served[clstIdx] = 1;
        }
    }

    printf("\nTotal Seek Time (SSTF): %d\n", total_dist);
    float avg = (float)total_dist / n;
    printf("Average Seek Time (SSTF): %f\n", avg);
}

int main() {
    int n;
    printf("Enter the number of reqs: ");
    scanf("%d", &n);

    DSA *reqs = malloc(n * sizeof(DSA));

    for (int i = 0; i < n; i++) {
        printf("Enter details for request %d:\n", i + 1);
        printf("Request ID: ");
        scanf("%d", &reqs[i].reqId);
        printf("Arrival Time Stamp: ");
        scanf("%d", &reqs[i].arrtstamp);
        printf("Cylinder: ");
        scanf("%d", &reqs[i].cyl);
        printf("Address: ");
        scanf("%d", &reqs[i].add);
        printf("Process ID: ");
        scanf("%d", &reqs[i].prid);
        printf("\n \n");
    }

    int strtpos;
    printf("Enter the starting position of the disk head: ");
    scanf("%d", &strtpos);

    FCFS(reqs, n, strtpos);
    SSTF(reqs, n, strtpos);

    free(reqs);
    return 0;
}

// SAMPLE INPUT

// Enter the number of reqs: 4
// Enter details for request 1:
// Request ID: 1
// Arrival Time Stamp: 0
// Cylinder: 45
// Address: 1000
// Process ID: 101

// Enter details for request 2:
// Request ID: 2
// Arrival Time Stamp: 1
// Cylinder: 30
// Address: 2000
// Process ID: 102

// Enter details for request 3:
// Request ID: 3
// Arrival Time Stamp: 2
// Cylinder: 10
// Address: 3000
// Process ID: 103

// Enter details for request 4:
// Request ID: 4
// Arrival Time Stamp: 3
// Cylinder: 75
// Address: 4000
// Process ID: 104

// Enter the starting position of the disk head: 50

// OUTPUT - DIY :p
