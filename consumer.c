#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer

pthread_mutex_t mutex;
sem_t empty, full;

void *producer(void *arg) {
    int item = *((int *)arg);

    while (1) {
        // Produce item
        // For simplicity, assume item is just an integer
        // You can replace this with actual data production

        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex);

        // Add item to buffer
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Signal that buffer is no longer empty
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex);

        // Consume item
        int item = buffer[count - 1];
        count--;
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal that buffer is no longer full
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    int producer_item = 1; // Example producer item

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, &producer_item);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up resources
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

