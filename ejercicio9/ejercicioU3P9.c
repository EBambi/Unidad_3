#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 16

int main(int argc, char *argv[])
{
    int pfd[2], pid, nbytes; /* Pipe file descriptors */
    char buf[BUF_SIZE];
    ssize_t numRead;

    if(pipe(pfd) < 0)
        exit(1);
    
    if(pid = fork() > 0){
        write(pfd[1],argv[1],BUF_SIZE);
        close(pfd[1]);
        while ((nbytes = read(pfd[0], buf, BUF_SIZE)) > 0)
            printf("%s\n", buf);
        if (nbytes != 0)
            exit(2);
        printf("Finished reading (father)\n");
        wait(NULL);
    }
    else{
        write(pfd[1],argv[2],BUF_SIZE);
        close(pfd[1]);
        while ((nbytes = read(pfd[0], buf, BUF_SIZE)) > 0)
            printf("%s\n", buf);
        if (nbytes != 0)
            exit(2);
        printf("Finished reading (son)\n");
    }
}