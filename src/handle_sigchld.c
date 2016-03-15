#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>

struct sigaction sigact;
sigact.sa_sigaction = &child_handler;
sigact.sa_flags = SA_SIGINFO;

void run_child() {
	pid_t Child = fork();
	if(Child < 0)
		printf(stderr,"Ошибка при порождении процесса\n");
	else if(Child == 0) {
		printf("Процесс-потомок: Я родился=)\n");
		printf("Пора на боковую\n");
		sleep(3);
		printf("Утро добрым не бывает...");
	}
	else if(Child > 0) {
		printf("Процесс-родитель\n");
		if(sigaction(SIGCHLD, sigact, NULL) == -1)
			printf("Ошибка при обработке сигнала SIGCHLD\n");
	}
}

void child_handler(int signum, siginfo_t *siginfo, void *context) {
	if(signum == SIGCHLD)
		printf("Принят сигнал SIGCHLD\n");
	else
		printf("Принят неопознанный сигнал: %d\n", signum);
}