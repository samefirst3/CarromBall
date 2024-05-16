#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex, wr;
int a=25, readcount=0;

void * reader(void * arg){
    printf("\n");
    long int num;
    num=(long int)arg;

    pthread_mutex_lock(&mutex);
    readcount++;
    pthread_mutex_unlock(&mutex);

    if(readcount==1)
        pthread_mutex_lock(&wr);

    printf("\nreader %ld entered in critical section",num);
    printf("\nreader %ld reads data as %d",num,a);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);
    printf("\nreader %ld left critical section",num);
    if(readcount==0)
        pthread_mutex_unlock(&wr);

}

void * writer(void * arg){
    printf("\n");

    long int num;
    num=(long int)arg;


    pthread_mutex_lock(&wr);
    printf("\nwriter %ld entered in critical section",num);
    printf("\nwriter %ld has written data as %d", num, ++a);
    printf("\nwriter %ld left critical section",num);
    sleep(1);
    pthread_mutex_unlock(&wr);


}

int main(){
    int n;
    pthread_t r[10],w[10];
    srand(time(NULL));
    long int i=0;
    long int j=0;

    //initialze mutex variables
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wr,NULL);

    //enter total number of readers and writers
    printf("enter total number of readers and writers: ");
    scanf("%d",&n);
    for(long int k=0;k<n;k++){
        int p=rand()%2;
        if(p==0){
            pthread_create(&r[i],NULL,reader, (void *)i);
            // pthread_join(r[i],NULL);
            i++;
        }else{
            pthread_create(&w[j],NULL,writer, (void *)j);
            // pthread_join(w[j],NULL);
            j++;
        }

    }

    for (long int k = 0; k < i; k++) {
        pthread_join(r[k], NULL);
    }

    // Join writer threads
    for (long int k = 0; k < j; k++) {
        pthread_join(w[k], NULL);
    }
    return 0;
}
