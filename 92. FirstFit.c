#include <stdio.h>

int main() {
    int i, j, N, M;

    printf("Enter number of memory blocks: ");
    scanf("%d", &N);
    int blocks[N];
    int originalBlocks[N];

    printf("Enter size of each memory block:\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &blocks[i]);
        originalBlocks[i] = blocks[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &M);
    int processes[M];
    int allocation[M];
    int fragments[M];

    printf("Enter size of each process:\n");
    for (i = 0; i < M; i++) {
        scanf("%d", &processes[i]);
        allocation[i] = -1;
        fragments[i] = 0;
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                fragments[i] = blocks[j] - processes[i];
                blocks[j] -= processes[i];
                break; // stop searching after first fit
            }
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
