#include<stdio.h>
#include<stdlib.h>
#define max 30

void sjf(){
    int i,j, n, bt[max], wt[max], tat[max], at[max],pid[max],temp;
    float wtavg, tatavg;
    printf("\nEnter the number of processes (MAX 30)-- ");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("\n Enter the burst time of process %d -- ", i);
        scanf("%d", &bt[i]);
        pid[i] = i;
    }
    wt[0] = wtavg = 0;
    tat[0] = tatavg = bt[0];

        for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(bt[j] > bt[j+1]){                
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
    for(i=1; i<n; i++){
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }
    printf("\n\t PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME\n");
    for(i=0; i<n; i++){
        printf("\n\t P[%d] \t\t %d \t\t %d \t\t %d", pid[i], bt[i], wt[i], tat[i]);
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
        printf("          %d", tat[i]);
    }
    printf("\n");



}
int main(){
    sjf();
    return 0;
}