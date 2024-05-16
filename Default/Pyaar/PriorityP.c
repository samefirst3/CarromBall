#include <stdio.h>
#include <limits.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], temp[n], ct[n], tat[n], wt[n], priority[n], seq[n], premptime[n];
    int completed = 0;
    int current_process = -1;
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
        ct[i] = 0;
        tat[i] = 0;
        wt[i] = 0;
        printf("Enter the priority of process %d: ", i + 1);
        scanf("%d", &priority[i]);
        printf("\n");
    }

    while (completed < n)
    {
        int min_priority = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && priority[i] < min_priority && bt[i] > 0)
            {
                min_priority = priority[i];
                min_index = i;
            }
        }

        // Preempt
        if (min_index != -1 && min_index != current_process)
        {
            if (current_process != -1 && bt[current_process] > 0)
            {
                wt[current_process]++;
            }
            seq[completed] = min_index;
            premptime[completed] = time;
            current_process = min_index;
        }

        if (current_process != -1 && --bt[current_process] == 0)
        {
            min_priority = INT_MAX;
            time++;
            ct[current_process] = time;
            tat[current_process] = ct[current_process] - at[current_process];
            wt[current_process] = tat[current_process] - temp[current_process];
            completed++;
            current_process = -1;
        }
        else
        {
            time++;
        }
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], temp[i], ct[i], tat[i], wt[i]);
    }

    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++)
    {
        printf("| P%d ", seq[i] + 1);
    }
    printf("|\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", premptime[i]);
    }
    printf("%d\n", ct[n - 1]);

    float avgTAT = 0;
    float avgWT = 0;

    for (int i = 0; i < n; i++)
    {
        avgTAT += tat[i];
        avgWT += wt[i];
    }

    avgTAT /= n;
    avgWT /= n;

    printf("Average TAT: %.2f\n", avgTAT);
    printf("Average WT: %.2f\n", avgWT);

    return 0;
}
