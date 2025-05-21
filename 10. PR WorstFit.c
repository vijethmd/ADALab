#include <stdio.h>

int main() {
    int i, j, N, M;

    printf("Enter number of memory blocks: ");
    scanf("%d", &N);
    int blocks[N];
    int originalBlocks[N];  // To keep original sizes for fragmentation display

    printf("Enter size of each memory block:\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &blocks[i]);
        originalBlocks[i] = blocks[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &M);
    int processes[M];
    int allocation[M];  // Stores block index allocated for each process, -1 if not allocated
    int fragments[M];   // Stores leftover fragment after allocation for each process

    printf("Enter size of each process:\n");
    for (i = 0; i < M; i++) {
        scanf("%d", &processes[i]);
        allocation[i] = -1; // Not allocated initially
        fragments[i] = 0;
    }

    for (i = 0; i < M; i++) {
        int worstIdx = -1;
        int maxSize = -1;

        for (j = 0; j < N; j++) {
            if (blocks[j] >= processes[i] && blocks[j] > maxSize) {
                maxSize = blocks[j];
                worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            fragments[i] = blocks[worstIdx] - processes[i]; // leftover memory
            blocks[worstIdx] -= processes[i];  // reduce block size
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\tFragment\n");
    for (i = 0; i < M; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\t\t%d\n", allocation[i] + 1, fragments[i]);
        } else {
            printf("Not Allocated\t-\n");
        }
    }

    return 0;
}
