#include<stdio.h>
#include<stdlib.h>
#define max 30

void fcfs(){
    int i,j, n, bt[max], wt[max], tat[max],ct[max], at[max],pid[max];
    float wtavg, tatavg;
    printf("\nEnter the number of processes (MAX 30)-- ");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("\n Enter the arrival time of process %d -- ", i);
        scanf("%d", &at[i]);
        pid[i] = i;
    }
    for(i=0; i<n; i++){
        printf("\n Enter the burst time of process %d -- ", i);
        scanf("%d", &bt[i]);
    }
    wt[0] = wtavg = 0;
    tat[0] = tatavg = bt[0];
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(at[j] > at[j+1]){
                // Swap arrival time
                int temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                // Swap process id
                temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;
            }
        }
    }
    /*for(i=0; i<n; i++){
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }*/

        for (int i = 0; i < n; i++)
    {
        wt[i]=0;
        tat[i]=0;
        for (int j = 0; j < i; j++)
        {

            wt[i] = wt[i]+bt[j];
        }
        ct[i]= ct[i-1]+bt[i];
        ct[0]= bt[0]+at[0];
        tat[i]= ct[i]-at[i];

        wtavg = wtavg+wt[i];
        tatavg= tatavg+tat[i];

        printf("%d\t\t\t%d\t\t%d\t\t%d", i+1, bt[i], wt[i], ct[i]);
        printf("\n");
    }

    printf("\n\t PROCESS \t ARRIVAL TIME \t BURST TIME \t WAITING TIME \t COMPLETION TIME \t TURNAROUND TIME\n");
    for(i=0; i<n; i++){
        printf("\n\t P[%d] \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d", pid[i], at[i], bt[i], wt[i], ct[i], tat[i]);
    }
    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);
        printf("\nGantt Chart:\n");
    printf(" ");
    for(i=0; i<n; i++){
        printf("-----------");
    }
    printf("\n|");
    for(i=0; i<n; i++){
        printf("   P[%d]   |", pid[i]);
    }
    printf("\n ");
    for(i=0; i<n; i++){
        printf("-----------");
    }
    printf("\n0");
    for(i=0; i<n; i++){
        printf("          %d", ct[i]);
    }

}
int main(){
    fcfs();
    return 0;
}
