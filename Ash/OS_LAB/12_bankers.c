#include <stdio.h>

// Maximum number of processes and resources
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to check if the system is in a safe state and print the safe sequence
int isSafe(int processes[], int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES], int n, int m, int safeSeq[])
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0}; // Initialize all processes as unfinished

    // Initialize work as available
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0; // Count of finished processes
    // Repeat until all processes are finished
    while (count < n)
    {
        int found = 0;
        // Find an unfinished process with needs <= work
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m)
                { // All needs <= work
                    // Release allocated resources and mark process as finished
                    for (int x = 0; x < m; x++)
                        work[x] += alloc[i][x];
                    finish[i] = 1;
                    safeSeq[count] = i; // Add the process to the safe sequence
                    count++;
                    found = 1;
                }
            }
        }
        if (!found)   // No such process found
            return 0; // System is not in a safe state
    }

    return 1; // System is in a safe state
}

int main()
{
    int n, m;                                // Number of processes and resources
    int processes[MAX_PROCESSES];            // Process IDs
    int available[MAX_RESOURCES];            // Available resources
    int max[MAX_PROCESSES][MAX_RESOURCES];   // Maximum demand of each process
    int alloc[MAX_PROCESSES][MAX_RESOURCES]; // Resources allocated to each process
    int need[MAX_PROCESSES][MAX_RESOURCES];  // Remaining needs of each process
    int safeSeq[MAX_PROCESSES];              // Array to store the safe sequence

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Input the process IDs
    printf("Enter the process IDs: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i]);

    // Input the available resources
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Input the maximum demand of each process
    printf("Enter the maximum demand matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input the resources allocated to each process
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Calculate the remaining needs of each process
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Check if the system is in a safe state and print the safe sequence
    if (isSafe(processes, available, max, alloc, need, n, m, safeSeq))
    {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d", processes[safeSeq[i]]);
            if (i != n - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        printf("System is not in a safe state.\n");
    }

    return 0;
}