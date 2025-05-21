#include <stdio.h>

struct Process {
    int PID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int PRIORITY;
    int DONE;
};

int main() {
    int N, i, current = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &N);

    struct Process P[N];

    for (i = 0; i < N; i++) {
        P[i].PID = i + 1;
        printf("Enter AT, BT, and PRIORITY for Process %d: ", P[i].PID);
        scanf("%d %d %d", &P[i].AT, &P[i].BT, &P[i].PRIORITY);
        P[i].DONE = 0;
    }

    while (completed < N) {
        int idx = -1;
        int highestPriority = -1;

        for (i = 0; i < N; i++) {
            if (P[i].AT <= current && P[i].DONE == 0) {
                if (P[i].PRIORITY > highestPriority) {
                    highestPriority = P[i].PRIORITY;
                    idx = i;
                } else if (P[i].PRIORITY == highestPriority) {
                    if (P[i].AT < P[idx].AT) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (current < P[idx].AT) {
                current = P[idx].AT;
            }

            P[idx].CT = current + P[idx].BT;
            P[idx].TAT = P[idx].CT - P[idx].AT;
            P[idx].WT = P[idx].TAT - P[idx].BT;
            P[idx].DONE = 1;
            completed++;
            current = P[idx].CT;
        } else {
            current++;
        }
    }

    printf("\nPID\tAT\tBT\tPRIORITY\tCT\tTAT\tWT\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               P[i].PID, P[i].AT, P[i].BT, P[i].PRIORITY,
               P[i].CT, P[i].TAT, P[i].WT);
    }

    return 0;
}
