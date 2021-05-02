#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define PERMS 0644

struct my_msgbuf {
   long mtype;
   char mtext[200];
};

void *sendMsg(void*);
void *recvMsg(void*);

int main(void) {
        
    int msqid1, msqid2;
    key_t key1, key2;
    pthread_t threadSend;
    pthread_t threadRecv;

    system("touch msgq1.txt");
    
    if ((key1 = ftok("msgq1.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    
    if ((msqid1 = msgget(key1, PERMS | IPC_CREAT)) == -1) {
        perror("msgget1");
        exit(1);
    }

    if ((key2 = ftok("msgq2.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    
    if ((msqid2 = msgget(key2, PERMS)) == -1) {
        perror("msgget2");
        exit(1);
    }

    pthread_create(&threadSend, NULL, &sendMsg, msqid1);
    pthread_create(&threadRecv, NULL, &recvMsg, msqid2);

    pthread_join(threadSend,NULL);
    pthread_join(threadRecv,NULL);

    return 0;
}

void *sendMsg(void *msqid){
    struct my_msgbuf buf;
    int len;
    printf("[1]: ");
    buf.mtype = 1;
    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
        len = strlen(buf.mtext);

        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
        if (msgsnd(msqid, &buf, len+1, 0) == -1)
        perror("msgsnd1");
    }
    strcpy(buf.mtext, "end");
    len = strlen(buf.mtext);
    if (msgsnd(msqid, &buf, len+1, 0) == -1)
    perror("msgsnd");
    
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("message queue [1]: done sending messages.\n");
}

void *recvMsg(void *msqid){
    struct my_msgbuf buf;
    int toend;
    
    for(;;) { 
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv1");
            exit(1);
        }
        printf("\n/r[2]: \"%s\"\n", buf.mtext);
        toend = strcmp(buf.mtext,"fin");
        if (toend == 0)
        break;
    }
    printf("message queue 1: done receiving messages.\n");
    system("rm msgq1.txt");
}