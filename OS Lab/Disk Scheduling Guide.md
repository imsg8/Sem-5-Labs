
# Disk Scheduling Algorithms: FCFS and SSTF

## 1. FCFS (First-Come, First-Serve) Disk Scheduling

### **What is FCFS?**
- **FCFS (First-Come, First-Serve)** processes requests in the **order they arrive**.
- It **does not optimize seek time**, meaning it processes each request sequentially, even if a closer request is available.

---

### **Code for FCFS Disk Scheduling:**

```c
void FCFS(DSA requests[], int n, int start) {
    int current_position = start;   // Starting position of the disk head
    int total_distance = 0;         // Total seek time

    printf("\nFCFS Disk Scheduling:\n");
    printf("Move from %d to %d\n", current_position, requests[0].cyl);

    for (int i = 0; i < n; i++) {
        int distance = abs(current_position - requests[i].cyl);  // Calculate distance
        total_distance += distance;                              // Accumulate total seek time
        current_position = requests[i].cyl;                      // Move disk head

        printf("Move from %d to %d with Seek %d (Request ID: %d, Process ID: %d)\n",
               current_position, requests[i].cyl, distance, requests[i].reqId, requests[i].prid);
    }

    printf("\nTotal Seek Time (FCFS): %d\n", total_distance);
    float avg = (float)total_distance / n;
    printf("Average Seek Time (FCFS): %f\n", avg);
}
```

---

### **Explanation:**
1. **Initialization:**
   - `current_position` stores the starting position of the disk head.
   - `total_distance` accumulates the total seek time.

2. **Processing Requests:**
   - For each request, the disk head moves from the current position to the request's cylinder.
   - The **absolute difference** between the two cylinders is added to the total seek time.

3. **Output:**
   - After all requests are processed, the total and average seek time are printed.

---

## 2. SSTF (Shortest Seek Time First) Disk Scheduling

### **What is SSTF?**
- **SSTF (Shortest Seek Time First)** selects the request with the **smallest seek time** from the current position.
- It **minimizes the total seek time** but can cause **starvation** for distant requests.

---

### **Code for SSTF Disk Scheduling:**

```c
void SSTF(DSA requests[], int n, int start) {
    int current_position = start;         // Initial disk head position
    int total_distance = 0;               // Total seek time
    int served[n];                        // Mark requests as served
    for (int i = 0; i < n; i++) served[i] = 0;

    printf("\nSSTF Disk Scheduling:\n");

    for (int count = 0; count < n; count++) {
        int closest_index = -1;
        int closest_distance = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!served[i]) {   // Check only unserved requests
                int distance = abs(current_position - requests[i].cyl);
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_index = i;
                }
            }
        }

        if (closest_index != -1) {
            total_distance += closest_distance;
            printf("Move from %d to %d with Seek %d (Request ID: %d, Process ID: %d)\n",
                   current_position, requests[closest_index].cyl, closest_distance, 
                   requests[closest_index].reqId, requests[closest_index].prid);
            current_position = requests[closest_index].cyl;
            served[closest_index] = 1; // Mark as served
        }
    }

    printf("\nTotal Seek Time (SSTF): %d\n", total_distance);
    float avg = (float)total_distance / n;
    printf("Average Seek Time (SSTF): %f\n", avg);
}
```

---

### **Explanation:**
1. **Initialization:**
   - `current_position` holds the disk head's starting position.
   - `total_distance` keeps track of the cumulative seek time.
   - The `served` array marks which requests have been processed.

2. **Finding the Closest Request:**
   - For each iteration, the algorithm finds the **closest unserved request**.
   - It calculates the absolute distance between the disk head and the request's cylinder.

3. **Processing the Closest Request:**
   - Once found, the disk head moves to the closest cylinder.
   - The **distance** is added to the **total seek time**.
   - The request is marked as **served**.

---

## **Comparison of FCFS and SSTF**

| **Aspect**            | **FCFS**                          | **SSTF**                          |
|-----------------------|------------------------------------|-----------------------------------|
| **Order of Processing** | Sequential (arrival order)      | Selects the closest request      |
| **Seek Time**           | Can be high                     | Minimized by choosing nearest   |
| **Complexity**          | Simple and easy to implement    | Slightly more complex            |
| **Starvation**          | No starvation                   | Can cause starvation for distant requests |

---

## **How to Memorize for Exams:**

1. **FCFS:**
   - Think of **FCFS** as a **bank queue**—requests are processed in the order they arrive.
   - Memorize the logic: **"First come, first served, no matter the distance."**

2. **SSTF:**
   - Imagine **SSTF** as **delivering packages**—you pick the nearest destination first.
   - Use the phrase: **"Shortest first, optimize the distance."**

3. **Practice the Code by Hand:**
   - Write out both algorithms multiple times to reinforce the syntax and logic.
   - Understand how **loops and conditions** work in both algorithms.

4. **Visualize Disk Movement:**
   - Visualizing how the disk head moves between requests will help solidify the concepts.

---

This document covers **FCFS and SSTF disk scheduling algorithms** with code, explanations, and a comparison to help you prepare effectively for your exams.
