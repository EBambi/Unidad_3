#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    sem_t *sem = sem_open("semEjemplo",0);

    if(sem == SEM_FAILED){
        perror("Error al crear en post: ");
        exit(EXIT_FAILURE);
    }

    printf("pSemPost %d sem_post()... \n",getpid());
    if(sem_post(sem) == -1){
        perror("Error post: ");
        exit(EXIT_FAILURE);
    }

    printf("pSemPost %d succeeded\n",getpid());
    if(sem_close(sem) == -1){
        perror("Error al cerrar en Post: ");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}