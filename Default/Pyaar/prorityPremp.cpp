#include <bits/stdc++.h>
using namespace std;

struct Process {
    int processID;
    int burstTime;
    int remainingTime; // Remaining burst time
    int responseTime;
    int arrivalTime;
    int priority;
    int outTime;
    int inTime;
};

void insert(Process Heap[], Process value, int* heapSize, int* currentTime) {
    int start = *heapSize, i;
    Heap[*heapSize] = value;
    if (Heap[*heapSize].inTime == -1)
        Heap[*heapSize].inTime = *currentTime;
    ++(*heapSize);

    while (start != 0 && Heap[(start - 1) / 2].priority > Heap[start].priority) {
        swap(Heap[(start - 1) / 2], Heap[start]);
        start = (start - 1) / 2;
    }
}

void order(Process Heap[], int* heapSize, int start) {
    int smallest = start;
    int left = 2 * start + 1;
    int right = 2 * start + 2;

    if (left < *heapSize && Heap[left].priority < Heap[smallest].priority)
        smallest = left;

    if (right < *heapSize && Heap[right].priority < Heap[smallest].priority)
        smallest = right;

    if (smallest != start) {
        swap(Heap[smallest], Heap[start]);
        order(Heap, heapSize, smallest);
    }
}

Process extractMinimum(Process Heap[], int* heapSize, int* currentTime) {
    Process min = Heap[0];

    if (min.responseTime == -1)
        min.responseTime = *currentTime - min.arrivalTime;

    --(*heapSize);

    if (*heapSize >= 1) {
        Heap[0] = Heap[*heapSize];
        order(Heap, heapSize, 0);
    }

    return min;
}

bool compare(Process p1, Process p2) {
    return (p1.arrivalTime < p2.arrivalTime);
}

void scheduling(Process Heap[], Process array[], int n, int* heapSize, int* currentTime) {
    if (*heapSize == 0)
        return;

    Process min = extractMinimum(Heap, heapSize, currentTime);
    min.outTime = *currentTime + 1;
    --min.remainingTime;

    printf("Process ID = %d Current Time = %d\n", min.processID, *currentTime);

    if (min.remainingTime > 0) {
        insert(Heap, min, heapSize, currentTime);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (array[i].processID == min.processID) {
            array[i] = min;
            break;
        }
    }
}

void priorityPreemptive(Process array[], int n) {
    sort(array, array + n, compare);

    int totalWaitingTime = 0, totalBurstTime = 0,
        totalTurnaroundTime = 0, i, insertedProcesses = 0,
        heapSize = 0, currentTime = array[0].arrivalTime,
        totalResponseTime = 0;

    Process Heap[4 * n];

    for (int i = 0; i < n; i++) {
        totalBurstTime += array[i].burstTime;
        array[i].remainingTime = array[i].burstTime;
    }

    do {
        if (insertedProcesses != n) {
            for (i = 0; i < n; i++) {
                if (array[i].arrivalTime == currentTime) {
                    ++insertedProcesses;
                    array[i].inTime = -1;
                    array[i].responseTime = -1;
                    insert(Heap, array[i], &heapSize, &currentTime);
                }
            }
        }

        scheduling(Heap, array, n, &heapSize, &currentTime);
        ++currentTime;

        if (heapSize == 0 && insertedProcesses == n)
            break;
    } while (1);

    for (int i = 0; i < n; i++) {
        totalResponseTime += array[i].responseTime;
        totalWaitingTime += (array[i].outTime - array[i].inTime - array[i].burstTime);
        totalBurstTime += array[i].burstTime;
    }

    printf("Average Waiting Time = %f\n", (static_cast<float>(totalWaitingTime) / n));
    printf("Average Response Time = %f\n", (static_cast<float>(totalResponseTime) / n));
    printf("Average Turnaround Time = %f\n", (static_cast<float>(totalWaitingTime + totalBurstTime) / n));
}

int main() {
    int n, i;
    Process processes[5];
    
    processes[0] = {1, 6, 6, -1, 4, 2, -1, -1};
    processes[1] = {4, 3, 3, -1, 5, 1, -1, -1};
    processes[2] = {2, 1, 1, -1, 5, 3, -1, -1};
    processes[3] = {3, 2, 2, -1, 1, 4, -1, -1};
    processes[4] = {5, 4, 4, -1, 3, 5, -1, -1};

    priorityPreemptive(processes, 5);
    return 0;
}
