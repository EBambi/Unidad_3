#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 64

int main(int argc, char *argv[])
{
    int pfd[2], psn[2]; /* Pipe file descriptors */
    char buf[BUF_SIZE], msgMin[BUF_SIZE], msgMay[BUF_SIZE];
    ssize_t numRead;

    if (pipe(pfd) == -1){ /* Create the pipe */
        perror("pipe pfd");
        exit(EXIT_FAILURE);
    }

    if (pipe(psn) == -1){ /* Create the pipe */
        perror("pipe psn");
        exit(EXIT_FAILURE);
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0: /* Child  - reads from pipe */
        if (close(pfd[1]) == -1)
        {
            perror("close write - child");
            exit(EXIT_FAILURE);
        }
        if (close(psn[0]) == -1)
        {
            perror("close read - child");
            exit(EXIT_FAILURE);
        }
        numRead = read(pfd[0], buf, BUF_SIZE);
        int i = 0;
        while(buf[i]){
            msgMay[i] = toupper(buf[i]);
            i++;
        }
        write(psn[1],msgMay,BUF_SIZE);
        if (close(pfd[0]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (close(psn[1]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    default: /* Parent - writes to pipe */
        if (close(pfd[0]) == -1)
        {
            perror("close read - parent");
            exit(EXIT_FAILURE);
        }
        if (close(psn[1]) == -1)
        {
            perror("close write - parent");
            exit(EXIT_FAILURE);
        }
        scanf("%s",buf);
        int j = 0;
        while(buf[j]){
            msgMin[j] = tolower(buf[j]);
            j++;
        }
        write(pfd[1], msgMin, BUF_SIZE);
        read(psn[0],buf,BUF_SIZE);
        printf("Texto final: %s\n", buf);
        if (close(pfd[1]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (close(psn[0]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}