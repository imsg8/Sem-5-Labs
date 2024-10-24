# Table of Contents
- [Lab - 5: Processes and Signals](#lab---5-processes-and-signals)
- [Lab - 6: IPC – 1: Pipe, FIFO](#lab---6-ipc--1-pipe-fifo)
- [Lab - 7: IPC – 2: Message Queue, Shared Memory](#lab---7-ipc--2-message-queue-shared-memory)
  

# Lab - 5: Processes and Signals

## Overview
This section focuses on how the operating system manages processes and handles communication and synchronization between them using system calls.

---

## Process Management System Calls

### 1. `getpid()` and `getppid()`
These functions retrieve the process identifiers (PID) and parent process identifiers (PPID).

```c
#include <sys/types.h>
#include <unistd.h>

pid_t getpid(void);   // Get process ID
pid_t getppid(void);  // Get parent process ID
```

**Example**:
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    return 0;
}
```

---

### 2. `fork()`
The `fork()` function creates a new process by duplicating the current one. The child process receives a PID of 0.

```c
pid_t fork(void);
```

**Example**:
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        printf("Child process\n");
    } else {
        printf("Parent process\n");
    }
    return 0;
}
```

---

## Process Synchronization

### 1. `wait()`
The `wait()` function allows a parent process to wait until a child process terminates.

```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
```

**Example**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        exit(0);
    } else {
        wait(NULL);
        printf("Parent process\n");
    }
    return 0;
}
```

---

## Executing New Programs

### 1. `exec()`
The `exec()` family of functions replaces the current process image with a new one.

**Syntax**:
```c
int execlp(const char *file, const char *arg, ...);
```

**Example**:
```c
#include <unistd.h>

int main() {
    execlp("ls", "ls", "-l", NULL);
    return 0;
}
```

---

## Signals

### 1. `kill()`
The `kill()` system call sends a signal to a process, typically used to terminate it.

**Syntax**:
```c
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);
```

**Example**:
```c
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        while (1) { sleep(1); }
    } else {
        sleep(5);
        kill(pid, SIGKILL);
    }
    return 0;
}
```

---

## Lab Exercises
1. **Fork and Wait**: Implement a program where the parent waits for the child to complete.
2. **Exec Example**: Create a child process that runs a different program using `exec()`.
3. **Zombie Process**: Create a child process that exits without being waited on by the parent, resulting in a zombie process.

---

## Additional Exercises
1. **Orphan Process**: Create a child process that continues running after the parent exits, becoming an orphan.
2. **Signal Handling**: Modify a program to handle termination signals using the `signal()` function.

---



# Lab - 6: IPC – 1: Pipe, FIFO

## Introduction
Inter-Process Communication (IPC) allows processes to exchange data. **Pipes** and **FIFOs** are commonly used methods in Linux for IPC.

---

## Pipes
Pipes allow data transfer between **parent** and **child** processes. Pipes are **unidirectional**, meaning data flows from one end to another in one direction only.

### Creating a Pipe: `pipe()`
```c
#include <unistd.h>
int pipe(int pipefd[2]);
```
- **pipefd[0]**: File descriptor for reading.
- **pipefd[1]**: File descriptor for writing.
- **Returns**: 0 on success, -1 on error.

### Example: Pipe between Parent and Child Process
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {  // Child process
        close(fd[0]);  // Close unused read end
        char msg[] = "Hello from Child!";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    } else {  // Parent process
        close(fd[1]);  // Close unused write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s
", buffer);
        close(fd[0]);
    }

    return 0;
}
```
This example demonstrates a **child process writing data** to the parent process using a pipe.

---

## FIFOs (Named Pipes)
Unlike pipes, **FIFOs** are named pipes that allow communication between **unrelated processes**. FIFOs behave like regular files but maintain **data order**.

### Creating a FIFO: `mkfifo()`
```c
#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);
```
- **pathname**: Name of the FIFO.
- **mode**: Permissions for the FIFO (e.g., `0777`).

### Example: Producer-Consumer using FIFO
#### Producer Program
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *fifo = "/tmp/my_fifo";

    // Create FIFO
    mkfifo(fifo, 0666);

    // Open FIFO for writing
    fd = open(fifo, O_WRONLY);
    char message[] = "Data from Producer!";
    write(fd, message, strlen(message) + 1);
    close(fd);

    return 0;
}
```

#### Consumer Program
```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *fifo = "/tmp/my_fifo";
    char buffer[100];

    // Open FIFO for reading
    fd = open(fifo, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("Consumer received: %s
", buffer);
    close(fd);

    return 0;
}
```
In this example:
- **Producer** writes data to the FIFO.
- **Consumer** reads data from the same FIFO.

---

## Key Differences between Pipe and FIFO
| Feature          | Pipe                         | FIFO                          |
|------------------|------------------------------|-------------------------------|
| Directionality   | Unidirectional               | Unidirectional                |
| Communication    | Between related processes    | Between unrelated processes   |
| Name             | No name                      | Named (exists in the filesystem) |

---

## Lab Exercises
1. **Pipe**: Write a C program to create a pipe, and transfer data from child to parent.
2. **FIFO**: Implement a Producer-Consumer model using FIFOs.

---



# Lab - 7: IPC – 2: Message Queue, Shared Memory

## Message Queues
Message queues provide a mechanism for passing messages between unrelated processes, ensuring asynchronous communication. Here are the essential functions used:

### Creating a Message Queue: `msgget()`
```c
#include <sys/msg.h>

int msgget(key_t key, int msgflg);
```
- **key**: Unique identifier (use `IPC_PRIVATE` for a private queue).
- **msgflg**: Flags (e.g., `IPC_CREAT` to create a new queue).
- **Returns**: Positive message queue ID or -1 on failure.

Example:
```c
int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
if (msgid == -1) {
    perror("msgget failed");
}
```

---

### Sending a Message: `msgsnd()`
```c
int msgsnd(int msqid, const void *msg_ptr, size_t msg_sz, int msgflg);
```
- **msqid**: Message queue ID.
- **msg_ptr**: Pointer to the message (structure starting with `long int`).
- **msg_sz**: Size of the message (excluding `long int` type).
- **msgflg**: Flags (e.g., `IPC_NOWAIT` for non-blocking send).

Example:
```c
struct msg_st {
    long int type;
    char text[100];
};
struct msg_st message = {1, "Hello"};
msgsnd(msgid, (void *)&message, sizeof(message.text), 0);
```

---

### Receiving a Message: `msgrcv()`
```c
int msgrcv(int msqid, void *msg_ptr, size_t msg_sz, long int msgtype, int msgflg);
```
- **msgtype**: Retrieve message with specific type or first available (if 0).
- **Returns**: Number of bytes received or -1 on failure.

Example:
```c
struct msg_st received;
msgrcv(msgid, (void *)&received, sizeof(received.text), 1, 0);
printf("Received: %s", received.text);
```

---

### Controlling Message Queues: `msgctl()`
```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```
- **cmd**: Command (e.g., `IPC_RMID` to remove the queue).
- **buf**: Optional structure for queue information.

---

## Shared Memory
Shared memory enables multiple processes to access the same memory segment, making it efficient for large data exchange.

### Creating Shared Memory: `shmget()`
```c
int shmget(key_t key, size_t size, int shmflg);
```
- **key**: Shared memory ID.
- **size**: Size of memory to allocate.
- **shmflg**: Flags (e.g., `IPC_CREAT` to create the segment).

Example:
```c
int shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
if (shmid == -1) {
    perror("shmget failed");
}
```

---

### Attaching to Shared Memory: `shmat()`
```c
void *shmat(int shm_id, const void *shm_addr, int shmflg);
```
- **Returns**: Pointer to shared memory or (void *) -1 on failure.

Example:
```c
void *shared_mem = shmat(shmid, NULL, 0);
if (shared_mem == (void *)-1) {
    perror("shmat failed");
}
```

---

### Detaching from Shared Memory: `shmdt()`
```c
int shmdt(const void *shm_addr);
```
- **Returns**: 0 on success, -1 on failure.

---

### Controlling Shared Memory: `shmctl()`
```c
int shmctl(int shm_id, int cmd, struct shmid_ds *buf);
```
- **cmd**: Command (e.g., `IPC_RMID` to remove the segment).

Example:
```c
shmctl(shmid, IPC_RMID, 0);
```

---

## Example Programs

### Message Queue Example
```c
// Sender Program
struct msg_st msg = {1, "Test Message"};
msgsnd(msgid, &msg, sizeof(msg.text), 0);
```

### Shared Memory Example
```c
// Writer
char *data = (char *) shared_mem;
strcpy(data, "Shared Memory Example");
```
---
