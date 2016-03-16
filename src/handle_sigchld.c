#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct sigaction sigact;

void child_handler(int signum, siginfo_t *siginfo, void *context) {
	if(signum == SIGCHLD) {
		printf("Принят сигнал SIGCHLD\n");
		printf("PID=%i\n",siginfo->si_pid);
		printf("User=%i\n",siginfo->si_uid);
		printf("Status=%i\n",siginfo->si_status);
		printf("User time=%ld\n",siginfo->si_utime/CLOCKS_PER_SEC);
		printf("System time=%ld\n",siginfo->si_stime/CLOCKS_PER_SEC);
	}
	else
		printf("Принят неопознанный сигнал: %d\n", signum);
}

void run_child() {
	printf("Обработка сигнала SIGCHLD\n");
	sigact.sa_sigaction = &child_handler;
	sigact.sa_flags = SA_SIGINFO;
	pid_t Child = fork();
	if(Child < 0)
		printf("Ошибка при порождении процесса\n");
	else if(Child == 0) {
		printf("Процесс-потомок: Я родился=)\n");
		printf("Пора на боковую\n");
		sleep(3);
		printf("Я проснулся:)");
	}
	else if(Child > 0) {
		printf("Процесс-родитель\n");
		if(sigaction(SIGCHLD, &sigact, NULL) == -1)
			printf("Ошибка при обработке сигнала SIGCHLD\n");
		int status;
		if(wait(&status)<0)
			printf("Дети-зомби атакуют!!!");
	}
}