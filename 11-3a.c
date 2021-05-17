#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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

  srand(time(NULL));

  clientstruct.message.pid = getpid();
  clientstruct.message.numb = rand();
  clientstruct.mtype = 1;

  printf("Клиент отправил сообщение. тип = %ld, сообщение = '%f'\n", clientstruct.mtype, clientstruct.message.numb);

  if (msgsnd(msqid, &clientstruct, sizeof(clientstruct.message), 0) < 0) {
    printf("Сообщение не отправлено\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }

  printf("Дождитесь сообщения с сервера\n");

  if (msgrcv(msqid, &serverstruct, sizeof(serverstruct.message), getpid(), 0) < 0) {
    printf("Сообщение не получено\n");
    exit(-1);
  }
  
  printf("Сообщение с сервера: %f\n", serverstruct.message.numb);

  return 0;
}