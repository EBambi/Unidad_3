#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


#define SH_SIZE 16

int main(int argc, char * argv[]){

    int shm_fd = shm_open("shm0", O_CREAT | O_RDWR, 0600);
    if (shm_fd < 0) {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd);

    if (ftruncate(shm_fd, SH_SIZE * sizeof(char)) < 0) {
        perror("Truncation failed: ");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "The memory region is truncated.\n");

    void* map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (map == MAP_FAILED) {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }

    char* ptr = (char*)map;
    ptr[0] = 'A';
    ptr[1] = 'B';
    ptr[2] = 'C';
    ptr[3] = '\n';
    ptr[4] = '\0';

    fprintf(stdout, "Data is written to the shared memory.\n");

    if (munmap(ptr, SH_SIZE) < 0) {
        perror("Unmapping failed: ");
        exit(EXIT_FAILURE);
    }


    if (close(shm_fd) < 0) {
        perror("Closing shm failed: ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}