#include <stdio.h>

struct Process {
    int PID;
    int AT;
    int BT;
    int RT;
    int CT;
    int TAT;
    int WT;
    int VISITED;
};

int main() {
    int N, TIME_QUANTUM, i, current = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &N);

    struct Process P[N];
    int queue[N * 10];
    int front = 0, rear = 0;

    for (i = 0; i < N; i++) {
        P[i].PID = i + 1;
        printf("Enter AT and BT for Process %d: ", P[i].PID);
        scanf("%d %d", &P[i].AT, &P[i].BT);
        P[i].RT = P[i].BT;
        P[i].VISITED = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &TIME_QUANTUM);

    // Sort by Arrival Time
    for (i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (P[j].AT > P[j + 1].AT) {
                struct Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    // Enqueue first process
    queue[rear++] = 0;
    P[0].VISITED = 1;
    current = P[0].AT;

    while (front < rear) {
        int idx = queue[front++];
        if (P[idx].RT > TIME_QUANTUM) {
            current += TIME_QUANTUM;
            P[idx].RT -= TIME_QUANTUM;
        } else {
            current += P[idx].RT;
            P[idx].RT = 0;
            P[idx].CT = current;
            P[idx].TAT = P[idx].CT - P[idx].AT;
            P[idx].WT = P[idx].TAT - P[idx].BT;
            completed++;
        }

        // Enqueue newly arrived processes
        for (i = 0; i < N; i++) {
            if (P[i].AT <= current && P[i].VISITED == 0) {
                queue[rear++] = i;
                P[i].VISITED = 1;
            }
        }

        // If current process still has time, requeue it
        if (P[idx].RT > 0) {
            queue[rear++] = idx;
        }

        // If queue is empty but processes remain, jump to next arrival
        if (front == rear && completed < N) {
            for (i = 0; i < N; i++) {
                if (P[i].VISITED == 0) {
                    queue[rear++] = i;
                    P[i].VISITED = 1;
                    current = P[i].AT > current ? P[i].AT : current;
                    break;
                }
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < N; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", P[i].PID, P[i].AT, P[i].BT, P[i].CT, P[i].TAT, P[i].WT);
    }

    return 0;
}
