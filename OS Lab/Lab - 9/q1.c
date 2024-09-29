#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int fib[100];
void* child_thread(void* param) {
    int id = (long)param;
    fib[id] = (id < 2) ? id : fib[id - 1] + fib[id - 2];
    return 0;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    pthread_t thread[100];
    for (int i = 0; i < n; i++)
        pthread_create(&thread[i], 0, child_thread, (void*)(long)i);
    for (int i = 0; i < n; i++)
        pthread_join(thread[i], 0);
    for (int i = 0; i < n; i++)
        printf("%d ", fib[i]);
}
