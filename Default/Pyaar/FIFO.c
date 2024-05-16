
#include <stdio.h>
int main()
{
    int i, j, n, ref_str[50], frame[10], no, k, avail, fcount = 0; 
    printf("\n ENTER THE NUMBER OF PAGES : ");
    scanf("%d", &n); 
    printf("\n ENTER THE REFERENCE STRING :\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &ref_str[i]);
    printf("\n ENTER THE NUMBER OF FRAMES : ");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
        frame[i] = -1; 
    j = 0;             // initialize page frame pointer
    printf("\n ref string    \tpage frames     \tHit/Fault\n");
    for (i = 1; i <= n; i++)
    {
        printf("%d\t\t", ref_str[i]);
        avail = 0; //default value
        for (k = 0; k < no; k++)
            if (frame[k] == ref_str[i]) 
            {
                avail = 1; 
                for (k = 0; k < no; k++)
                    printf("%d\t", frame[k]); 
                printf("H");                 
            }
        if (avail == 0)
        {
            frame[j] = ref_str[i]; 
            j = (j + 1) % no;     
            fcount++;             
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]); 
            printf("F");                
        }
        printf("\n");
    }
    printf("\nPage Fault Is: %d", fcount);
    printf("\nPage Hit Is: %d", (n - fcount));
    printf("\nPage Fault Ratio Is: %.2f", ((float)fcount/n));
    printf("\nPage Hit Ratio Is: %.2f", ((float)(n - fcount)/n));
    return 0;
}
