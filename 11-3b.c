#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct client
{
    long mtype;

    struct
    {
        pid_t pid;
        float numb;
    } message;
} clientstruct;

struct server
{
    long mtype;

    struct
    {
    	float numb;
    } message;
} serverstruct;


int main(void)
{
    int msqid;
    char pathname[]="11-3b.c";
    key_t  key;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Ключ не сгенерирован\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("msqid не получен\n");
        exit(-1);
    }

    while(1) {
        if (msgrcv(msqid, (struct clientbuf *) &clientstruct, sizeof(clientstruct.message), 1, 0) < 0) {
            printf("Сообщение не получено\n");
            exit(-1);
        }

        printf("Клиент с pid = %d сообщение: %f\n", clientstruct.message.pid, clientstruct.message.numb);

        serverstruct.message.numb = clientstruct.message.numb;
        serverstruct.mtype = clientstruct.message.pid;

        if (msgsnd(msqid, &serverstruct, sizeof(serverstruct.message), 0) < 0) {
          printf("Сообщение не получено\n");
          msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
          exit(-1);
        }
        
        printf("Сервер отправил сообщение клиенту\n");
    }
  return 0;
}