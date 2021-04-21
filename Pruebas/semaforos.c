#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 100
#define LOOPS 1000000

// 1. declarar la varible para referencir el mutex
pthread_mutex_t sum_mutex;
long sum = 0;

void  *doWork(void *pdata){
    long i;

    for(i= 0; i<LOOPS;i++){
        // 3. Entrar a la región crítica
        pthread_mutex_lock(&sum_mutex);
        sum = sum + 1;
        // 4.  Salir de la región crítica
        pthread_mutex_unlock(&sum_mutex);
    } 
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    pthread_t threads[NTHREADS];
  
    // 2. Inicializar el mutex
    pthread_mutex_init(&sum_mutex,NULL);

    for(int i = 0;i<NTHREADS;i++){
        pthread_create(&threads[i],NULL,doWork,NULL);
    }

    for(int i = 0;i<NTHREADS;i++){
        pthread_join(threads[i],NULL);
    }
    
    pthread_mutex_destroy(&sum_mutex);
    
    printf("Thread sum: %ld\n",sum);
    sum = 0;
    for(int i = 0; i<NTHREADS*LOOPS;i++){
        sum = sum +1;
    }
    printf("Check sum : %ld\n",sum);

    pthread_exit(NULL);
}