#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int fibo[10];

void* child_thread(void *param) {
    int id = (int)param;
    if (id == 0 || id == 1)
        fibo[id] = id;
    else {
        fibo[id] = fibo[id - 1] + fibo[id - 2];
    }
    return (void *)id;
}
int main(int argc, char *argv[]) {
    pthread_t thread[10];
    int return_value[10];
    int n;
    n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        pthread_create(&thread[i], 0, &child_thread, (void*)i);
        pthread_join(thread[i], (void**)&return_value[i]);
    }
    printf("Fibo sequence: ");
    for (int i = 0; i < n; i++)
        printf("%d ", fibo[i]);
}
