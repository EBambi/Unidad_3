#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 64

int main(int argc, char *argv[])
{
    int pfd[2], psn[2];
    char bufP[BUF_SIZE], bufS[BUF_SIZE];
    ssize_t numRead;

    if (pipe(pfd) == -1){
        perror("pipe pfd");
        exit(EXIT_FAILURE);
    }

    if (pipe(psn) == -1){
        perror("pipe psn");
        exit(EXIT_FAILURE);
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0: /* Hijo */
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
        for(;;){
            numRead = read(pfd[0],bufS,BUF_SIZE);
            int i = 0;
            while(bufS[i]){
                bufS[i] = toupper(bufS[i]);
                i++;
            }
            write(psn[1],bufS,BUF_SIZE);
        }
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
    default: /* Padre */
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
        for(;;){
            scanf("%s",bufP);
            int j = 0;
            while(bufP[j]){
                bufP[j] = tolower(bufP[j]);
                j++;
            }
            write(pfd[1],bufP,BUF_SIZE);
            read(psn[0],bufS,BUF_SIZE);
            printf("Texto Pipe: %s\n", bufS);
        }
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
    }
}