#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    
    mode_t permisos = 0666;
    int flags = O_CREAT;

    unsigned int value = 0;

    sem_t *sem = sem_open("semEjemplo",flags,permisos,value);

    if(sem == SEM_FAILED){
        perror("Error al crear el semáforo: ");
        exit(EXIT_FAILURE);
    }
    
    if(sem_close(sem) == -1){
        perror("Error al cerrar el semáforo: ");
        exit(EXIT_FAILURE);        
    }

    exit(EXIT_SUCCESS);
}