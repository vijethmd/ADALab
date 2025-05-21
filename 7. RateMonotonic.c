#include <stdio.h>

struct Process {
    int pid;
    int execution_time;
    int period;
    int remaining_time;
    int deadline;
    int instances;
};

int main() {
    int n, hyper_period = 1;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter execution time and period for P%d: ", i + 1);
        scanf("%d %d", &p[i].execution_time, &p[i].period);
        p[i].remaining_time = 0;
        p[i].deadline = p[i].period;
        // LCM for hyperperiod (simplified as product if prime periods)
        hyper_period *= p[i].period;
    }

    // Sort by period (Rate Monotonic: shorter period = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].period > p[j].period) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\nRMS Scheduling from t=0 to t=%d\n", hyper_period);
    for (int t = 0; t < hyper_period; t++) {
        // Release jobs at their period
        for (int i = 0; i < n; i++) {
            if (t % p[i].period == 0) {
                p[i].remaining_time = p[i].execution_time;
                p[i].deadline = t + p[i].period;
            }
        }

        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                idx = i; // select highest priority (shortest period)
                break;
            }
        }

        if (idx != -1) {
            printf("Time %d: Process P%d is running\n", t, p[idx].pid);
            p[idx].remaining_time--;
        } else {
            printf("Time %d: CPU is idle\n", t);
        }

        // Check for missed deadlines
        for (int i = 0; i < n; i++) {
            if (t + 1 == p[i].deadline && p[i].remaining_time > 0) {
                printf("Deadline missed by Process P%d at time %d!\n", p[i].pid, t + 1);
            }
        }
    }

    return 0;
}
