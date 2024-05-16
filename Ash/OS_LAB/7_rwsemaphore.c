#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t db;
sem_t x;
int readerCount = 0;

void *reader(void *arg)
{

    sem_wait(&x);
    readerCount++;
    printf("Reader %ld entered db\n", (long)arg);
    if (readerCount == 1)
    {
        sem_wait(&db);
    }
    printf("Reader %ld is reading...\n", (long)arg);

    sem_post(&x);

    sem_wait(&x);
    readerCount--;
    printf("Reader %ld exited from db\n", (long)arg);
    if (readerCount == 0)
    {
        sem_post(&db);
    }
    sem_post(&x);

    pthread_exit(NULL);
}

void *writer(void *arg)
{

    sem_wait(&db);
    printf("Writer %ld entered db\n", (long)arg);
    printf("Writer %ld is writing...\n", (long)arg);
    sem_post(&db);
    printf("Writer %ld exited from db\n", (long)arg);

    pthread_exit(NULL);
}

int main()
{
    pthread_t readers[5], writers[5];
    sem_init(&db, 0, 1);
    sem_init(&x, 0, 1);

    for (long i = 0; i < 5; i++)
    {
        pthread_create(&readers[i], NULL, reader, (void *)i);
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&db);
    sem_destroy(&x);

    return 0;
}