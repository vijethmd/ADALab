#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Declare variable length arrays (VLAs)
    int Allocation[n][m];
    int Max[n][m];
    int Need[n][m];
    int Available[m];
    int Work[m];
    bool Finish[n];
    int safeSequence[n];

    // Input Allocation matrix
    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    // Input Max matrix
    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    // Input Available resources
    printf("\nEnter Available Resources (%d values):\n", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &Available[j]);
    }

    // Calculate Need matrix = Max - Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Initialize Work and Finish
    for (int j = 0; j < m; j++) {
        Work[j] = Available[j];
    }
    for (int i = 0; i < n; i++) {
        Finish[i] = false;
    }

    // Safety algorithm
    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            break; // No process can proceed safely
        }
    }

    // Output result
    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state. Deadlock possible.\n");
    }

    return 0;
}
