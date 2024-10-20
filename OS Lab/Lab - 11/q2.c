#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define maxres 5
#define maxt 10

int avl[maxres];
int maxi[maxt][maxres];
int allocation[maxt][maxres];
int need[maxt][maxres];
int num_threads, num_resources;

pthread_mutex_t lock;

bool is_safe(int thread_id) {
    int work[maxres];
    bool finish[maxt] = {false};
    
    for (int i = 0; i < num_resources; i++)
        work[i] = avl[i];
    
    for (int i = 0; i < num_threads; i++) {
        if (!finish[i]) {
            bool can_allocate = true;
            for (int j = 0; j < num_resources; j++) {
                if (need[i][j] > work[j]) {
                    can_allocate = false;
                    break;
                }
            }
            if (can_allocate) {
                finish[i] = true;
                for (int j = 0; j < num_resources; j++)
                    work[j] += allocation[i][j];
                i = -1;
            }
        }
    }
    
    for (int i = 0; i < num_threads; i++)
        if (!finish[i])
            return false;
    return true;
}

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    while (1) {
        int request[maxres];
        for (int i = 0; i < num_resources; i++)
            request[i] = rand() % (maxi[thread_id][i] - allocation[thread_id][i] + 1);
        
        pthread_mutex_lock(&lock);
        
        bool can_allocate = true;
        for (int i = 0; i < num_resources; i++) {
            if (request[i] > avl[i] || request[i] > need[thread_id][i]) {
                can_allocate = false;
                break;
            }
        }
        
        if (can_allocate) {
            for (int i = 0; i < num_resources; i++) {
                avl[i] -= request[i];
                allocation[thread_id][i] += request[i];
                need[thread_id][i] -= request[i];
            }
            
            if (is_safe(thread_id)) {
                printf("Thread %d: Request granted\n", thread_id);
            } else {
                for (int i = 0; i < num_resources; i++) {
                    avl[i] += request[i];
                    allocation[thread_id][i] -= request[i];
                    need[thread_id][i] += request[i];
                }
                printf("Thread %d: Request denied (unsafe state)\n", thread_id);
            }
        } else {
            printf("Thread %d: Request denied (insufficient resources)\n", thread_id);
        }
        
        pthread_mutex_unlock(&lock);
        
        // Simulate some work
        usleep(rand() % 1000000);
        
        // Release some resources
        pthread_mutex_lock(&lock);
        for (int i = 0; i < num_resources; i++) {
            int release = rand() % (allocation[thread_id][i] + 1);
            allocation[thread_id][i] -= release;
            avl[i] += release;
            need[thread_id][i] += release;
        }
        printf("Thread %d: Resources released\n", thread_id);
        pthread_mutex_unlock(&lock);
        
        usleep(rand() % 1000000);
    }
    
    return NULL;
}

int main() {
    srand(time(NULL));
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    
    printf("Enter the avl resources:\n");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &avl[i]);
    
    printf("Enter the maxi resources for each thread:\n");
    for (int i = 0; i < num_threads; i++)
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &maxi[i][j]);
    
    for (int i = 0; i < num_threads; i++)
        for (int j = 0; j < num_resources; j++) {
            allocation[i][j] = 0;
            need[i][j] = maxi[i][j];
        }
    
    pthread_mutex_init(&lock, NULL);
    
    pthread_t threads[maxt];
    int thread_ids[maxt];
    
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
    
    pthread_mutex_destroy(&lock);
    
    return 0;
}
