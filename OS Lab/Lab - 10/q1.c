#include <stdio.h>
#include <stdbool.h>
#define MAX_PROC 15
#define RES 3

int alloc[MAX_PROC][RES], max[MAX_PROC][RES], need[MAX_PROC][RES], avail[RES];

void calcNeed(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < RES; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe(int n) {
    int work[RES], safeSeq[MAX_PROC], count = 0;
    bool finish[MAX_PROC] = {false};
    
    for (int i = 0; i < RES; i++) work[i] = avail[i];

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < RES; j++)
                    if (need[p][j] > work[j]) break;
                
                if (j == RES) {
                    for (j = 0; j < RES; j++) work[j] += alloc[p][j];
                    safeSeq[count++] = p;
                    finish[p] = found = true;
                }
            }
        }
        if (!found) {
            printf("Unsafe state\n");
            return false;
        }
    }
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}

bool request(int pid, int req[], int n) {
    for (int j = 0; j < RES; j++) {
        if (req[j] > need[pid][j] || req[j] > avail[j]) {
            printf("Invalid request\n");
            return false;
        }
    }
    
    for (int j = 0; j < RES; j++) {
        avail[j] -= req[j];
        alloc[pid][j] += req[j];
        need[pid][j] -= req[j];
    }
    
    if (isSafe(n)) {
        printf("Request granted\n");
        return true;
    } else {
        for (int j = 0; j < RES; j++) {
            avail[j] += req[j];
            alloc[pid][j] -= req[j];
            need[pid][j] += req[j];
        }
        printf("Request denied\n");
        return false;
    }
}

int main() {
    int n, pid, req[RES];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < RES; j++)
            scanf("%d", &max[i][j]);
    
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < RES; j++)
            scanf("%d", &alloc[i][j]);
    
    printf("Enter available resources:\n");
    for (int j = 0; j < RES; j++)
        scanf("%d", &avail[j]);
    
    calcNeed(n);
    isSafe(n);
    
    printf("Enter process ID for request: ");
    scanf("%d", &pid);
    printf("Enter request vector: ");
    for (int j = 0; j < RES; j++)
        scanf("%d", &req[j]);
    
    request(pid, req, n);
    
    return 0;
}
