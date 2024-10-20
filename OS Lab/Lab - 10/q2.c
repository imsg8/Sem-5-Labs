#include <stdio.h>
#include <stdlib.h>

typedef struct proc {
    int id, bt, pr;
    struct proc* next;
} proc;

typedef struct Queue {
    proc *front, *rear;
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

void enqueue(Queue* q, proc* p) {
    if (!q->rear) q->front = p;
    else q->rear->next = p;
    q->rear = p;
}

proc* dequeue(Queue* q) {
    if (!q->front) return NULL;
    proc* temp = q->front;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    temp->next = NULL;
    return temp;
}

int roundRobin(Queue* q) {
    proc* p = dequeue(q);
    if (!p) return 0;
    printf("RR: proc %d for %d units\n", p->id, q->quantum);
    if ((p->bt -= q->quantum) > 0) enqueue(q, p);
    else free(p);
    return 1;
}

int pr(Queue* q) {
    if (!q->front) return 0;
    proc *p = q->front, *hp = p, *prev = NULL;
    for (proc* cur = p; cur->next; prev = cur, cur = cur->next)
        if (cur->next->pr < hp->pr) hp = cur->next, p = cur;
    if (p) p->next = hp->next;
    if (q->rear == hp) q->rear = p;
    printf("PR: proc %d (pr %d)\n", hp->id, hp->pr);
    if ((hp->bt -= q->quantum) > 0) enqueue(q, hp);
    else free(hp);
    return 1;
}

int fcfs(Queue* q) {
    proc* p = dequeue(q);
    if (!p) return 0;
    printf("FCFS: proc %d completed\n", p->id);
    free(p);
    return 1;
}

int main() {
    Queue *q1 = createQueue(4, roundRobin), 
          *q2 = createQueue(8, pr), 
          *q3 = createQueue(0, fcfs);

    enqueue(q1, &(proc){1, 10, 3, NULL});
    enqueue(q1, &(proc){2, 6, 5, NULL});
    enqueue(q2, &(proc){3, 8, 2, NULL});
    enqueue(q2, &(proc){4, 7, 1, NULL});
    enqueue(q3, &(proc){5, 4, 4, NULL});

    while (q1->front || q2->front || q3->front) {
        if (q1->schedule(q1) || q2->schedule(q2)) continue;
        q3->schedule(q3);
    }

    free(q1); free(q2); free(q3);
    return 0;
}
