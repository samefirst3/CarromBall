#include <stdio.h>
// 7
// 0
// 1
// 2
// 0
// 3
// 0
// 4
// 2
// 3
// 0
// 3
// 2
// 1
// 2
void lruPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int pageFaults = 0;
    int hits = 0;
    int recentCount = 0;
    int recent[capacity];
    int hit = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }

    printf("\n ref string    \tpage frames     \tHit/Fault\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already present in the frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                pageFound = 1;
                recent[j] = recentCount++;
                hits++;
                hit = 1;
                break;
            }
        }

        if (!pageFound) {
            // Page is not present, find the least recently used page in the frame
            int lruIndex = 0;
            for (int j = 1; j < capacity; j++) {
                if (recent[j] < recent[lruIndex]) {
                    lruIndex = j;
                }
            }

            // Replace the least recently used page with the new page
            frame[lruIndex] = page;
            recent[lruIndex] = recentCount++;
            pageFaults++;
        }

        // Print the current page and frame status
        printf("%d\t\t", page);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d\t\t", frame[j]);
            else
                printf("-\t\t");
        }
        hit == 1 ? printf("\tH") : printf("\tF");
        printf("\n");
        hit = 0;
    }

    printf("\nPage Fault Is: %d", pageFaults);
    printf("\nPage Hit Is: %d", hits);
    printf("\nPage Fault Ratio Is: %.2f", ((float)pageFaults/n));
    printf("\nPage Hit Ratio Is: %.2f", ((float)hits/n));
}

int main() {
    int n;

    printf("\n ENTER THE NUMBER OF PAGES : ");
    scanf("%d", &n);

    int pages[n];

     printf("\n ENTER THE REFERENCE STRING :\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int capacity;

    printf("\n ENTER THE NUMBER OF FRAMES : ");
    scanf("%d", &capacity);

    lruPageReplacement(pages, n, capacity);

    return 0;
}
