#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define bs 8

sem_t es;
sem_t fs;
int buffer[bs];
int in = 0, out = 0;

void *producer(void *arg)
{
    int item = 1;

    while (1)
    {

        printf("Produced item: %d\n", item);

        sem_wait(&es);

        buffer[in] = item;
        in = (in + 1) % bs;

        sem_post(&fs);

        item++;
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    while (1)
    {

        sem_wait(&fs);

        int consumed = buffer[out];
        printf("Consumed item: %d\n", consumed);

        out = (out + 1) % bs;

        sem_post(&es);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t producerThread, consumerThread;
    sem_init(&es, 0, bs);
    sem_init(&fs, 0, 0);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&es);
    sem_destroy(&fs);

    return 0;
}