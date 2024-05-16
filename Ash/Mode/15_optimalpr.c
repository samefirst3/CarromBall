#include <stdio.h>
#include <limits.h>

int findOptimalPage(int pages[], int frame[], int n, int capacity, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < capacity; i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (frame[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If the page is not present in the future pages, return it.
        if (j == n)
            return i;
    }

    return (res == -1) ? 0 : res;
}

void optimalPageReplacement(int pages[], int n, int capacity)
{
    int frame[capacity];
    int pageFaults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    printf("Incoming\tFrame\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already present in the frame
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == page)
            {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound)
        {
            int replaceIndex = findOptimalPage(pages, frame, n, capacity, i);

            frame[replaceIndex] = page;
            pageFaults++;
        }

        // Print the current page and frame status
        printf("%d\t\t", page);
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] != -1)
                printf("%d\t\t", frame[j]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main()
{
    int n;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    // Input the sequence of page requests
    printf("Enter the sequence of page requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int capacity;

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    optimalPageReplacement(pages, n, capacity);

    return 0;
}