#include <stdio.h>

struct Process {
    int PID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int DONE;
};

int main() {
    int N, i, j, current = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &N);

    struct Process P[N];

    for (i = 0; i < N; i++) {
        P[i].PID = i + 1;
        printf("Enter AT and BT for Process %d: ", P[i].PID);
        scanf("%d %d", &P[i].AT, &P[i].BT);
        P[i].DONE = 0;
    }

    while (completed < N) {
        int idx = -1;
        int minBT = 1e9;

        for (i = 0; i < N; i++) {
            if (P[i].AT <= current && P[i].DONE == 0) {
                if (P[i].BT < minBT) {
                    minBT = P[i].BT;
                    idx = i;
                } else if (P[i].BT == minBT) {
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
            current = P[idx].CT;
            completed++;
        } else {
            current++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].PID, P[i].AT, P[i].BT, P[i].CT, P[i].TAT, P[i].WT);
    }

    return 0;
}
