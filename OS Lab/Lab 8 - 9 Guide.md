# Table of Contents
- [Lab - 8: IPC – 3: DEADLOCK, LOCKING, SYNCHRONIZATION](#lab---8-ipc--3-deadlock-locking-synchronization)
- [Lab - 9: Programs on Threads](#lab---9-programs-on-threads)


# Lab - 8: IPC – 3: DEADLOCK, LOCKING, SYNCHRONIZATION

## 1. Deadlocks
A deadlock occurs when multiple processes are waiting on each other to release resources, and none of them can proceed.

### Deadlock Conditions
1. **Mutual Exclusion**: Only one process can access a resource at a time.
2. **Hold and Wait**: Processes holding resources can request new ones.
3. **No Preemption**: A resource can only be released voluntarily by the process holding it.
4. **Circular Wait**: A closed chain of processes exists, where each process holds a resource needed by the next process in the chain.

### Handling Deadlocks
- **Deadlock Avoidance**: Algorithms ensure the system never enters a circular-wait condition.
- **Safe State**: System guarantees all processes can complete execution without deadlock.
- Example: **Banker’s algorithm**.

---

## 2. Synchronization Primitives

### Mutex Locks
- A **mutex** allows only one thread to access critical code at a time.

#### Usage
```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&mutex);  // Lock
// Critical Section
pthread_mutex_unlock(&mutex);  // Unlock
pthread_mutex_destroy(&mutex);  // Destroy
```

---

### Semaphores
- Semaphores manage access to shared resources and allow multiple threads to access simultaneously.

#### Semaphore API Functions
- **Initialization**: `sem_init(&sem, 0, 1);`
- **Wait**: `sem_wait(&sem);`
- **Post**: `sem_post(&sem);`
- **Destroy**: `sem_destroy(&sem);`

---

## 3. Data Races and Solutions
A **data race** occurs when multiple threads access shared data without synchronization.

```c
void update(int* a) {
    *a = *a + 4;
}
```

#### Solution: Using Mutex
Wrap shared data accesses with `pthread_mutex_lock()` and `pthread_mutex_unlock()`.

---

## 4. Practical Code for Deadlocks
Example of improper semaphore usage leading to deadlock:

```c
sem_t sem1, sem2;

void* task1(void* arg) {
    sem_wait(&sem1);
    sem_wait(&sem2);
    // Critical section
    sem_post(&sem2);
    sem_post(&sem1);
}

void* task2(void* arg) {
    sem_wait(&sem2);
    sem_wait(&sem1);
    // Critical section
    sem_post(&sem1);
    sem_post(&sem2);
}
```

---

## 5. Detecting Deadlocks
- **Banker’s Algorithm** ensures the system grants resource requests only if it stays in a safe state.

---

## 6. Synchronization and Thread Programming
- Threads allow concurrent execution within processes.
- Synchronization mechanisms like **mutexes** and **semaphores** are essential to prevent data races.

---

## 7. Tools for Detecting Data Races
- **Helgrind** (part of Valgrind) detects race conditions.
```bash
gcc -g race.c -lpthread
valgrind --tool=helgrind ./a.out
```


# Lab - 9: Programs on Threads

## Overview
Multithreading in shell scripting involves the creation and management of multiple threads within a process. 
A thread, also called a lightweight process, allows concurrent execution of different parts of a program, 
enhancing performance and efficiency.

## Syntax for Creating and Managing Threads

### 1. Creating a Thread
The `pthread_create()` function is used to create a new thread.

**Syntax:**
```c
int pthread_create(
    pthread_t *thread,           // Pointer to a thread identifier to store the thread ID
    const pthread_attr_t *attr,  // Pointer to thread attributes (default if NULL)
    void *(*start_routine)(void *),  // Function to execute in the thread
    void *arg                     // Argument to pass to the start_routine function
);
```

**Example:**
```c
#include <pthread.h>
#include <stdio.h>

void* thread_function(void* arg) {
    printf("Inside the thread function\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);  // Wait for the thread to finish
    printf("In the main thread\n");
    return 0;
}
```
This example creates a thread that prints a message, while the main thread waits for the child thread to complete using `pthread_join()`.

---

### 2. Thread Termination
A thread automatically terminates when the function it executes returns. Alternatively, `pthread_exit()` can be used to terminate a thread.

**Syntax:**
```c
void pthread_exit(void *retval);
```

**Example:**
```c
void* thread_function(void* arg) {
    printf("Thread exiting...\n");
    pthread_exit(NULL);  // Explicit thread termination
}
```

---

### 3. Passing Data to Threads
You can pass arguments to a thread by casting them to `void*`. 

**Example:**
```c
void* print_number(void* arg) {
    int number = *(int*)arg;
    printf("Received number: %d\n", number);
    return NULL;
}

int main() {
    pthread_t thread;
    int num = 42;
    pthread_create(&thread, NULL, print_number, &num);
    pthread_join(thread, NULL);
    return 0;
}
```
This example demonstrates passing an integer to a thread function.

---

### 4. Joining Threads
`pthread_join()` is used by the main thread to wait for another thread to complete.

**Syntax:**
```c
int pthread_join(pthread_t thread, void **retval);
```
- **`thread`**: Thread ID of the thread to join.
- **`retval`**: Pointer to store the return value from the thread (optional).

---

### 5. Thread Attributes
To customize thread behavior, attributes are set using `pthread_attr_t`.

**Example:**
```c
pthread_attr_t attr;
pthread_attr_init(&attr);  // Initialize the attribute object
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);  // Set as joinable
pthread_create(&thread, &attr, thread_function, NULL);
pthread_attr_destroy(&attr);  // Destroy the attribute object
```

---

## Lab Exercises

1. **Fibonacci Series with Threads:**  
   Create a thread to generate the Fibonacci series and print it from the main thread.

2. **Sum of Non-Negative Integers:**  
   Write a thread function to compute the sum of integers and return the result to the main thread.

3. **Prime Number Generation:**  
   Implement a multithreaded program to generate prime numbers between two ranges using threads.
