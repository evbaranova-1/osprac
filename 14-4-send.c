#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

int recipientPid;
int valueSent;
bool flag = true;

void receiver_signal_handler(int nsig) {
	flag = true;
}

void send_value() {
	int bits_count = sizeof(int) * 8;
	for (int i = 0; i < bits_count; ++i) {
		while (!flag);
		
		if ((valueSent & (1 << i)) != 0) {
			kill(recipientPid, SIGUSR1);
		}
		else {
			kill(recipientPid, SIGUSR2);
		}
		flag = false;
	}
	
	kill(recipientPid, SIGCHLD);
}

int main() {
	signal(SIGUSR1, receiver_signal_handler);
	printf("PID �����������: %d\n", (int)getpid());
	
	printf("������� PID ����������:\n");
	if (scanf("%d", &recipientPid) < 0) {
		printf("������ ��� ������ PID �����������\n");
		exit(-1);
	}
	
	printf("������� �������������� ����� �����:\n");
	if (scanf("%d", &valueSent) < 0) {
		printf("��� ������ ����� ��������� ������.\n");
		exit(-2);
	}
	
	send_value();
	return 0;
}
