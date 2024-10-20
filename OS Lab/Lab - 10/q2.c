#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Process {
    int id;
    int burst_time;
    int priority;
    struct Process* next;
} Process;

typedef struct Queue {
    Process* front;
    Process* rear;
    int quantum;
    int (*schedule)(struct Queue*);
} Queue;

Queue* createQueue(int quantum, int (*schedule)(Queue*)) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->quantum = quantum;
    q->schedule = schedule;
    return q;
}

void enqueue(Queue* q, Process* p) {
    if (q->rear == NULL) {
        q->front = q->rear = p;
        return;
    }
    q->rear->next = p;
    q->rear = p;
}

Process* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    Process* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    temp->next = NULL;
    return temp;
}

int roundRobin(Queue* q) {
    if (q->front == NULL) return 0;
    Process* p = dequeue(q);
    printf("Executing process %d for %d units\n", p->id, q->quantum);
    p->burst_time -= q->quantum;
    if (p->burst_time > 0) enqueue(q, p);
    else free(p);
    return 1;
}

int priority(Queue* q) {
    if (q->front == NULL) return 0;
    Process* p = q->front;
    Process* highest_priority = p;
    while (p->next != NULL) {
        if (p->next->priority < highest_priority->priority)
            highest_priority = p->next;
        p = p->next;
    }
    if (highest_priority == q->front) q->front = q->front->next;
    else {
        p = q->front;
        while (p->next != highest_priority) p = p->next;
        p->next = highest_priority->next;
    }
    if (q->rear == highest_priority) q->rear = p;
    highest_priority->next = NULL;
    printf("Executing process %d (priority %d) for %d units\n", 
           highest_priority->id, highest_priority->priority, q->quantum);
    highest_priority->burst_time -= q->quantum;
    if (highest_priority->burst_time > 0) enqueue(q, highest_priority);
    else free(highest_priority);
    return 1;
}

int fcfs(Queue* q) {
    if (q->front == NULL) return 0;
    Process* p = dequeue(q);
    printf("Executing process %d to completion\n", p->id);
    free(p);
    return 1;
}

int main() {
    Queue* q1 = createQueue(4, roundRobin);
    Queue* q2 = createQueue(8, priority);
    Queue* q3 = createQueue(0, fcfs);

    enqueue(q1, &(Process){1, 10, 3, NULL});
    enqueue(q1, &(Process){2, 6, 5, NULL});
    enqueue(q2, &(Process){3, 8, 2, NULL});
    enqueue(q2, &(Process){4, 7, 1, NULL});
    enqueue(q3, &(Process){5, 4, 4, NULL});

    while (q1->front || q2->front || q3->front) {
        if (q1->schedule(q1)) continue;
        if (q2->schedule(q2)) continue;
        q3->schedule(q3);
    }

    free(q1);
    free(q2);
    free(q3);

    return 0;
}
