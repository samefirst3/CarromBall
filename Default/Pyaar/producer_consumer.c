#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t empty, full;
pthread_mutex_t mutex;
int buffer[5];
int count=0;

void *producer(void *arg){
    long int num=(long int)arg;

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer[count]=rand()%50;
    printf("\n Producer %ld produced: %d \n", num+1, buffer[count]);
    count++;
    printf(" Buffer: ");
    for(int i=0;i<count;i++){
        printf("%d ", buffer[i]);
    }
    printf("\n");
    sleep(1);

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    pthread_exit(NULL);
}

void *consumer(void *arg){
    long int num=(long int)arg;

    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    count--;
    printf("\n Consumer %ld consumed: %d \n", num+1, buffer[count]);
    printf(" Buffer: ");
    for(int i=0;i<count;i++){
        printf("%d ", buffer[i]);
    }
    printf("\n");
    sleep(1);

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    pthread_exit(NULL);
}

int main(){
    int np, nc;
    pthread_t p[10], c[10];
    unsigned long int i,j,k,l;

    printf("Enter number of producers and number of consumers: ");
    scanf("%d %d",&np, &nc);

    sem_init(&empty,0,5); //variable name, not shared, initial value
    sem_init(&full,0,0);

    pthread_mutex_init(&mutex, NULL);

    //create producer and consumer threads
    for(i=0;i<np;i++)
        pthread_create(&p[i],NULL, producer, (void *)i);
    for(j=0;j<nc;j++)
        pthread_create(&c[j],NULL, consumer, (void *)j);

    //join the threads
    for(k=0;k<np;k++)
        pthread_join(p[k], NULL);
    for(l=0;l<nc;l++)
        pthread_join(c[l], NULL);
    return 0;
}
