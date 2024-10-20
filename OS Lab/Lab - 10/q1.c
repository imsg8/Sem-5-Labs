#include <stdio.h>
#include <stdbool.h>
#define max 15
#define res 3

int alloc[max][res], max[max][res], need[max][res], avail[res];

void calcNeed(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < res; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe(int n) {
    int work[res], safeSeq[max], count = 0;
    bool finish[max] = {false};
    
    for (int i = 0; i < res; i++) work[i] = avail[i];

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < res; j++)
                    if (need[p][j] > work[j]) break;
                
                if (j == res) {
                    for (j = 0; j < res; j++) work[j] += alloc[p][j];
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
    for (int j = 0; j < res; j++) {
        if (req[j] > need[pid][j] || req[j] > avail[j]) {
            printf("Invalid request\n");
            return false;
        }
    }
    
    for (int j = 0; j < res; j++) {
        avail[j] -= req[j];
        alloc[pid][j] += req[j];
        need[pid][j] -= req[j];
    }
    
    if (isSafe(n)) {
        printf("Request granted\n");
        return true;
    } else {
        for (int j = 0; j < res; j++) {
            avail[j] += req[j];
            alloc[pid][j] -= req[j];
            need[pid][j] += req[j];
        }
        printf("Request denied\n");
        return false;
    }
}

int main() {
    int n, pid, req[res];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < res; j++)
            scanf("%d", &max[i][j]);
    
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < res; j++)
            scanf("%d", &alloc[i][j]);
    
    printf("Enter available resources:\n");
    for (int j = 0; j < res; j++)
        scanf("%d", &avail[j]);
    
    calcNeed(n);
    isSafe(n);
    
    printf("Enter process ID for request: ");
    scanf("%d", &pid);
    printf("Enter request vector: ");
    for (int j = 0; j < res; j++)
        scanf("%d", &req[j]);
    
    request(pid, req, n);
    
    return 0;
}
