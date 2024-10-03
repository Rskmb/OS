#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2); // Simulate thinking time

        // Determine left and right fork
        int left_fork = id;
        int right_fork = (id + 1) % NUM_PHILOSOPHERS;

        // Ensure deadlock-free acquisition
        if (id % 2 == 0) {
            // Even philosopher: pick up left fork first
            sem_wait(&forks[left_fork]);
            sem_wait(&forks[right_fork]);
        } else {
            // Odd philosopher: pick up right fork first
            sem_wait(&forks[right_fork]);
            sem_wait(&forks[left_fork]);
        }

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2); // Simulate eating time

        // Release forks
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
        printf("Philosopher %d has finished eating.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Optional: Wait for threads (not needed in this infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up semaphores (not reached in this case)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

