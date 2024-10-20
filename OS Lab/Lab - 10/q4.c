#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_FRAMES 10

typedef struct {
    int page;
    bool second_chance;
} Frame;

int find_page(Frame *frames, int n_frames, int page) {
    for (int i = 0; i < n_frames; i++)
        if (frames[i].page == page)
            return i;
    return -1;
}

int main() {
    int n_frames, n_pages, page_faults = 0, clock_hand = 0;
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);
    
    Frame frames[MAX_FRAMES] = {{0}};
    
    printf("Enter number of pages: ");
    scanf("%d", &n_pages);
    
    int pages[n_pages];
    printf("Enter page reference string: ");
    for (int i = 0; i < n_pages; i++)
        scanf("%d", &pages[i]);
    
    for (int i = 0; i < n_pages; i++) {
        int page = pages[i];
        int index = find_page(frames, n_frames, page);
        
        if (index == -1) {
            page_faults++;
            while (frames[clock_hand].second_chance) {
                frames[clock_hand].second_chance = false;
                clock_hand = (clock_hand + 1) % n_frames;
            }
            frames[clock_hand].page = page;
            frames[clock_hand].second_chance = true;
            clock_hand = (clock_hand + 1) % n_frames;
        } else {
            frames[index].second_chance = true;
        }
    }
    
    printf("Total page faults: %d\n", page_faults);
    printf("Hit ratio: %.2f\n", (float)(n_pages - page_faults) / n_pages);
    
    return 0;
}