#include <stdio.h>

struct Process {
    int PID;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;     // Remaining Time
    int DONE;   // 1 if completed
};

int main() {
    int N, i, current = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &N);

    struct Process P[N];

    for (i = 0; i < N; i++) {
        P[i].PID = i + 1;
        printf("Enter AT and BT for Process %d: ", P[i].PID);
        scanf("%d %d", &P[i].AT, &P[i].BT);
        P[i].RT = P[i].BT;
        P[i].DONE = 0;
    }

    while (completed < N) {
        int idx = -1;
        int minRT = 1e9;

        for (i = 0; i < N; i++) {
            if (P[i].AT <= current && P[i].DONE == 0 && P[i].RT < minRT && P[i].RT > 0) {
                minRT = P[i].RT;
                idx = i;
            }
        }

        if (idx != -1) {
            P[idx].RT--;

            if (P[idx].RT == 0) {
                P[idx].CT = current + 1;
                P[idx].TAT = P[idx].CT - P[idx].AT;
                P[idx].WT = P[idx].TAT - P[idx].BT;
                P[idx].DONE = 1;
                completed++;
            }

            current++;
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
