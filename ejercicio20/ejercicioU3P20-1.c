#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 100
#define LOOPS 1000000
long sum = 0;

void  *doWork(void *pdata){
    long i;
    for(i= 0; i<LOOPS;i++) sum = sum + 1;
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    pthread_t threads[NTHREADS];

    for(int i = 0;i<NTHREADS;i++){
        pthread_create(&threads[i],NULL,doWork,NULL);
        pthread_join(threads[i],NULL);
    }

    // for(int i = 0;i<NTHREADS;i++){
    //     pthread_join(threads[i],NULL);
    // }
    printf("Thread sum: %ld\n",sum);
    sum = 0;
    for(int i = 0; i<NTHREADS*LOOPS;i++){
        sum = sum +1;
    }
    printf("Check sum : %ld\n",sum);
    pthread_exit(NULL);
}