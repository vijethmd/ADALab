#include <stdio.h>

int main() {
    int i, j, n, capacity, pageFaults = 0, idx = 0;

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

    for (i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frame (hit)
        for (j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            frames[idx] = pages[i];
            idx = (idx + 1) % capacity;  // FIFO index rotation
            pageFaults++;

            // Print frames status after this replacement
            printf("Page %d -> Frames: ", pages[i]);
            for (j = 0; j < capacity; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
