#include <pthread.h>
#include <stdio.h>

int s;
void* child_thread(void* param) {
    int x = (long)param;
    if (x > 0) s += x;
    return 0;
}

int main() {
    int n, x;
    pthread_t thread[100];
    printf("Enter number of numbers: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        pthread_create(&thread[i], 0, child_thread, (void*)(long)x);
        pthread_join(thread[i], 0);
    }
    printf("Sum of non-negative numbers is %d\n", s);
}
