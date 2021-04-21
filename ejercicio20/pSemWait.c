#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    sem_t *sem = sem_open("semEjemplo",0);

    if(sem == SEM_FAILED){
        perror("Error al crear el semáforo en wait");
        exit(EXIT_FAILURE);
    }

    printf("pSemWait %d sem_wait()...\n",getpid());
    if(sem_wait(sem) == -1){
        perror("Error al esperar el semáforo: ");
        exit(EXIT_FAILURE);
    }

    printf("pSemWait %d succeeded\n",getpid());
    if(sem_close(sem) == -1){
        perror("Error al cerrar el semáforo en wait: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("semEjemplo") == -1){
        perror("Error del unlink: ");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}