#include <stdio.h>

#define N 5

int state[N] = {0, 0, 0, 0, 0};
int chopstick[N] = {1, 1, 1, 1, 1};

void wait_chopstick(int i) {
    chopstick[i] = 0;
}

void signal_chopstick(int i) {
    chopstick[i] = 1;
}

int can_eat(int i) {
    int left = i;
    int right = (i + 1) % N;
    return chopstick[left] == 1 && chopstick[right] == 1;
}

void philosopher(int i) {
    printf("Philosopher %d is HUNGRY\n", i);
    state[i] = 1;

    if (can_eat(i)) {
        wait_chopstick(i);
        wait_chopstick((i + 1) % N);

        state[i] = 2;
        printf("Philosopher %d is EATING with chopsticks %d and %d\n", i, i, (i + 1) % N);

        signal_chopstick(i);
        signal_chopstick((i + 1) % N);
        state[i] = 0;
        printf("Philosopher %d has FINISHED EATING and is now THINKING\n", i);
    } else {
        printf("Philosopher %d can't eat now because chopsticks are not available\n", i);
    }
}

int main() {
    int i, rounds;

    printf("Dining Philosophers Problem Simulation (No Pointers, No Threads)\n\n");

    printf("Enter number of simulation rounds: ");
    scanf("%d", &rounds);

    for (int r = 0; r < rounds; r++) {
        printf("\n=== Round %d ===\n", r + 1);
        for (i = 0; i < N; i++) {
            philosopher(i);
        }
    }

    return 0;
}
