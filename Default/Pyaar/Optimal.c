#include <stdio.h>

// Function to find the key with minimum value in the map
int minFromMap(int mp[], int size) {
    int min = 100000;
    int min_key = -1;
    for (int i = 0; i < size; i++) {
        if (mp[i] <= min) {
            min = mp[i];
            min_key = i;
        }
    }
    return min_key;
}

int main() {
    printf("\n ENTER THE NUMBER OF PAGES : ");
    int n;
    scanf("%d", &n);
    
    int ref_str[n];
    
   printf("\n ENTER THE REFERENCE STRING :\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &ref_str[i]);
    
    printf("\n ENTER THE NUMBER OF FRAMES : ");
    int no;
    scanf("%d", &no);
    
    int frame[no];
    for (int i = 0; i < no; i++)
        frame[i] = -1;
    
    int mp[no]; // Using an array instead of unordered_map
    for (int i = 0; i < no; i++)
        mp[i] = 0;
    
    printf("\n ref string    \tpage frames     \tHit/Fault\n");
    
    int fcount = 0, hit = 0, flag = 0;
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t", ref_str[i]);
        flag = 0;
        
        for (int k = 0; k < no; k++) {
            if (frame[k] == ref_str[i]) {
                mp[ref_str[i]]--;
                flag = 1;
                printf("\t");
                
                for (k = 0; k < no; k++)
                    if (frame[k] != -1)
                        printf("%d\t", frame[k]);
                    else
                        printf("_\t");
                
                printf("\tH");
                hit++;
            }
        }
        
        if (flag == 0) {
            if (j < no) {
                frame[j] = ref_str[i];
                mp[ref_str[i]]--;
                j = (j + 1) % no;
                fcount++;
                
                printf("\t");
                for (int k = 0; k < no; k++)
                    if (frame[k] != -1)
                        printf("%d\t", frame[k]);
                    else
                        printf("_\t");
                
                printf("\tF\n");
                continue;
            } else {
                for (int x = 0; x < no; x++) {
                    if (frame[x] == minFromMap(mp, no)) {
                        frame[x] = ref_str[i];
                        break;
                    }
                }
                mp[ref_str[i]]--;
                fcount++;
                
                printf("\t");
                for (int k = 0; k < no; k++)
                    if (frame[k] != -1)
                        printf("%d\t", frame[k]);
                    else
                        printf("_\t");
                
                printf("\tF");
            }
        }
        printf("\n");
    }
    
    printf("\nPage Fault Is %d\n", fcount);
    printf("Page Hit Is %d\n", hit);
    printf("\nPage Fault Ratio Is: %.2f", ((float)fcount/n));
    printf("\nPage Hit Ratio Is: %.2f", ((float)hit
    /n));
    
    return 0;
}
