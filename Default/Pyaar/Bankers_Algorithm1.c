#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("\nEnter the number of resources: ");
    scanf("%d", &m);
    
    int alloc[n][m], max[n][m], avail[m], need[n][m];
    int f[n];   // finished array
    int ans[n]; // work or safe seq
    int ind = 0;
    
    printf("\nEnter the Allocation Matrix:\n");
    printf("A B C \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("\nEnter the Maximum need Matrix:\n");
    printf("A B C \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("\nEnter the Available Resources Matrix:\n");
    printf("A B C \n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    
    // Calculate Need Matrix
    printf("\nCalculating the Need Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    // Display table
    printf("\nProcess   Allocation   Max Need   Available   Remaining Need\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t", i);
        // Allocation
        for (j = 0; j < m; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\t");
        // Max Need
        for (j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t");
        // Available
        if (i == 0) {
            for (j = 0; j < m; j++) {
                printf("%d ", avail[j]);
            }
        }
        printf("\t");
        // Remaining Need
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    // Banker's Algorithm
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }
    
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("\nFollowing system is not in safe state\n");
            break;
        }
    }
    if (flag == 1) {
        printf("\nSafe Sequence is : ");
        printf("< ");
        for (i = 0; i < n; i++) {
            printf("P%d ", ans[i]);
        }
        printf(">");
    }
    printf("\n");
  
    return 0;
}
