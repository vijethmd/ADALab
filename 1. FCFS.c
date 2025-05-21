#include <stdio.h>

struct Process {
    int PID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

int main() {
    int N, i, j;
    int current = 0;

    printf("Enter number of processes: ");
    scanf("%d", &N);

    struct Process P[N];

    for (i = 0; i < N; i++) {
        P[i].PID = i + 1;
        printf("Enter AT and BT for Process %d: ", P[i].PID);
        scanf("%d %d", &P[i].AT, &P[i].BT);
    }

    // Selection Sort by Arrival Time
    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            if (P[i].AT > P[j].AT) {
                struct Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (current < P[i].AT) {
            current = P[i].AT;
        }

        P[i].CT = current + P[i].BT;
        P[i].TAT = P[i].CT - P[i].AT;
        P[i].WT = P[i].TAT - P[i].BT;

        current = P[i].CT;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].PID, P[i].AT, P[i].BT, P[i].CT, P[i].TAT, P[i].WT);
    }

    return 0;
}
