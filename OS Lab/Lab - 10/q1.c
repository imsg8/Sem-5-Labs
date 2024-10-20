#include <stdio.h>
#include <stdlib.h>

struct mab {
    int ofs;
    int size;
    int alctd;
    struct mab *next;
};
typedef struct mab Mab;
typedef Mab *MabPtr;

MabPtr createBlock(int ofs, int size, int alctd) {
    MabPtr block = (MabPtr)malloc(sizeof(Mab));
    block->ofs = ofs;
    block->size = size;
    block->alctd = alctd;
    block->next = NULL;
    return block;
}

MabPtr memChk(MabPtr m, int size) {
    while (m != NULL) {
        if (!m->alctd && m->size >= size) return m;
        m = m->next;
    }
    return NULL;
}

MabPtr memAlloc(MabPtr head, int size) {
    MabPtr block = memChk(head, size);
    if (block == NULL) {
        printf("Allocation failed. No suitable block found.\n");
        return NULL;
    }
    block->alctd = 1;
    if (block->size > size) memSplit(block, size);
    printf("alctd %d bytes at ofs %d.\n", size, block->ofs);
    return block;
}

MabPtr memSplit(MabPtr block, int size) {
    MabPtr newBlock = createBlock(block->ofs + size, block->size - size, 0);
    newBlock->next = block->next;
    block->next = newBlock;
    block->size = size;
    return block;
}

void memFree(MabPtr block) {
    block->alctd = 0;
    printf("Freed block at ofs %d.\n", block->ofs);
}

void memMerge(MabPtr head) {
    MabPtr current = head;
    while (current && current->next) {
        if (!current->alctd && !current->next->alctd) {
            current->size += current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void displayMemory(MabPtr head) {
    MabPtr current = head;
    printf("Memory Blocks:\n");
    while (current) {
        printf("ofs: %d, Size: %d, %s\n", 
               current->ofs, current->size, 
               current->alctd ? "alctd" : "Free");
        current = current->next;
    }
}

int main() {
    MabPtr head = createBlock(0, 100, 0);
    head->next = createBlock(100, 50, 1);
    head->next->next = createBlock(150, 200, 0);

    displayMemory(head);

    memAlloc(head, 30);
    displayMemory(head);

    memFree(head->next);
    memMerge(head);
    displayMemory(head);

    return 0;
}

// SAMPLE INPUT - OUTPUT

// Memory Blocks:
// Offset: 0, Size: 100, Free
// Offset: 100, Size: 50, Allocated
// Offset: 150, Size: 200, Free

// Allocated 30 bytes at offset 0.
// Memory Blocks:
// Offset: 0, Size: 30, Allocated
// Offset: 30, Size: 70, Free
// Offset: 100, Size: 50, Allocated
// Offset: 150, Size: 200, Free

// Freed block at offset 100.
// Memory Blocks:
// Offset: 0, Size: 30, Allocated
// Offset: 30, Size: 70, Free
// Offset: 100, Size: 250, Free
