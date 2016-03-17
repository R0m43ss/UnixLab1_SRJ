#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

struct sigaction sigact;
int sleep_time;

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
	sigact.sa_sigaction = &child_handler;
	sigact.sa_flags = SA_SIGINFO;
	pid_t Child = fork();
	if(Child < 0)
		perror("Ошибка при порождении процесса");
	else if(Child == 0) {
		printf("Потомок: Я родился:)\n");
		srand(time(NULL));
		sleep_time=rand()%5+1;
		printf("Пора на боковую. Разбудите через %i\n",sleep_time);
		sleep(sleep_time);
		printf("Я проснулся:)\n");
	}
	else if(Child > 0) {
		if(sigaction(SIGCHLD, &sigact, NULL) == -1) {
			perror("Ошибка при обработке сигнала SIGCHLD");
			exit(EXIT_FAILURE);
		}
		int status;
		if(waitpid(-1,&status,0)<0) {
			printf("Дети-зомби атакуют!!!\n");
			exit(EXIT_FAILURE);
		}
		else exit(EXIT_SUCCESS);
	}
}