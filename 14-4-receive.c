#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

int pidUser;
int index = 0;
int res = 0;
bool receivedByUser = false;

void sigusr1_handler_bit(int nsig) {
	res |= (1 << index++);
	kill(pidUser, SIGUSR1);
}

void sigusr2_handler_nobit(int nsig) {
	index++;
	kill(pidUser, SIGUSR1);
}

void sigchld_handler(int nsig) {
	receivedByUser = true;
}

int main() {
	printf("PID получения: %d\n", (int)getpid());
	
	printf("Введите PID отправителя:\n");
	scanf("%d", &pidUser);
	
	printf("Подожите результат\n");
	
	signal(SIGUSR1, sigusr1_handler_bit);
	signal(SIGUSR2, sigusr2_handler_nobit);
	signal(SIGCHLD, sigchld_handler);
	
	while (!receivedByUser);
	
	printf("Получено: %d\n", res);
	return 0;
}
