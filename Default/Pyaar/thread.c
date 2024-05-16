#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

int num[2] = {3,5} ;

void *thread_function(int *args){
    printf("Inside Thread Function.\n");
    int *x = args;
    int sum = x[0] + x[1];

    printf("Sum : %d\n",sum);
    pthread_exit("Sum Calculated");
}

int main(){
  const void *result;
    // Thread Creating
    pthread_t a_thread; // Thread Declaration
    pthread_create(&a_thread,NULL,thread_function,(void *)num);// Thread Created
    pthread_join(a_thread,&result); // Process waits for thread to finish.
    // Printing thread data
    printf("Inside Main Process\n");
    printf("Thread returned : %s\n",(char *)result);

}



