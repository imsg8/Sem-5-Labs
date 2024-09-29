#include <pthread.h>
#include <stdio.h>

int even_sum = 0, odd_sum = 0;

void* evesum(void* param) {
    int* arr = (int*)param;
    for (int i = 0; i < arr[0]; i++)
        if (arr[i + 1] % 2 == 0) even_sum += arr[i + 1];
    return 0;
}

void* oddsum(void* param) {
    int* arr = (int*)param;
    for (int i = 0; i < arr[0]; i++)
        if (arr[i + 1] % 2 != 0) odd_sum += arr[i + 1];
    return 0;
}

int main() {
    pthread_t t1, t2;
    int n, arr[100];
    printf("Enter number of elements: ");
    scanf("%d", &n);
    arr[0] = n;

    printf("Enter the elements:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);

    pthread_create(&t1, 0, evesum, (void*)arr);
    pthread_create(&t2, 0, sum_odd, (void*)arr);

    pthread_join(t1, 0);
    pthread_join(t2, 0);

    printf("Sum of even numbers: %d\n", even_sum);
    printf("Sum of odd numbers: %d\n", odd_sum);
}
