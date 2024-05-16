#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Process {
    int id;             // Process ID
    int burstTime;      // Burst time
    int remainingTime;  // Remaining burst time
};

void findAverageTime(vector<Process>& processes, int quantum) {
    int n = processes.size();
    vector<int> waitingTime(n, 0);
    int currentTime = 0;
    queue<int> readyQueue;

    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        readyQueue.push(i);
    }

    while (!readyQueue.empty()) {
        int currentProcess = readyQueue.front();
        readyQueue.pop();

        if (processes[currentProcess].remainingTime <= quantum) {
            currentTime += processes[currentProcess].remainingTime;
            waitingTime[currentProcess] = currentTime - processes[currentProcess].burstTime;
            processes[currentProcess].remainingTime = 0;
        } else {
            currentTime += quantum;
            processes[currentProcess].remainingTime -= quantum;
        }

        for (int i = 0; i < n; i++) {
            if (i != currentProcess && processes[i].remainingTime > 0 && processes[i].id <= currentTime) {
                readyQueue.push(i);
            }
        }

        if (processes[currentProcess].remainingTime > 0) {
            readyQueue.push(currentProcess);
        }
    }

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++) {
        int turnaroundTime = processes[i].burstTime + waitingTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime;
        cout << "P" << processes[i].id << "\t" << processes[i].burstTime << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime << endl;
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / n;
    float averageTurnaroundTime = static_cast<float>(totalTurnaroundTime) / n;

    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for Process P" << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;

    findAverageTime(processes, quantum);

    return 0;
}
