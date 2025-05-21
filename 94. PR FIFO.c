#include <stdio.h>

int main() {
    int i, j, n, capacity, pageFaults = 0, pageHits = 0, idx = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    int frames[capacity];
    for (i = 0; i < capacity; i++) {
        frames[i] = -1;  // initialize frames as empty
    }

    printf("\nPage\tFrame Status\t\tResult\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check for page hit
        for (j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        printf("%d\t", pages[i]);

        if (found) {
            pageHits++;
            // Print frames
            for (j = 0; j < capacity; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\t\tHIT\n");
        } else {
            // Page fault
            frames[idx] = pages[i];
            idx = (idx + 1) % capacity;
            pageFaults++;

            // Print frames
            for (j = 0; j < capacity; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\t\tFAULT\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits  : %d\n", pageHits);

    return 0;
}
