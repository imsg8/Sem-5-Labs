#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 100
#define SPARE_SIZE 10
#define FILE_SIZE 5

int disk[DISK_SIZE];
int spare[SPARE_SIZE];
int bad_block_table[DISK_SIZE];

void initialize_disk() {
    for (int i = 0; i < DISK_SIZE; i++) disk[i] = 0;
    for (int i = 0; i < DISK_SIZE; i++) bad_block_table[i] = -1;
}

void allocate_file(int start) {
    for (int i = start; i < start + FILE_SIZE; i++) {
        if (disk[i] == -1) {
            for (int j = 0; j < SPARE_SIZE; j++) {
                if (spare[j] == 0) {
                    spare[j] = 1;
                    bad_block_table[i] = DISK_SIZE + j;
                    printf("Bad block at %d, replaced by spare block %d\n", i, DISK_SIZE + j);
                    break;
                }
            }
        } else {
            disk[i] = 1;
        }
    }
}

void access_block(int block) {
    if (bad_block_table[block] != -1)
        printf("Accessing spare block %d (replaces bad block %d)\n", bad_block_table[block], block);
    else
        printf("Accessing block %d\n", block);
}

int main() {
    initialize_disk();

    disk[2] = -1;  
    disk[4] = -1;

    printf("Allocating file starting at block 0:\n");
    allocate_file(0);

    printf("\nAccessing all blocks of the file:\n");
    for (int i = 0; i < FILE_SIZE; i++) {
        access_block(i);
    }

    return 0;
}
