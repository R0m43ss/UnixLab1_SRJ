#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>

struct sigaction sigact;
sigact.sa_sigaction = &child_handler;
sigact.sa_flags = SA_SIGINFO;

void run_child() {
	pid_t Child = fork();
	if(Child < 0)
		fprintf(stderr,"Ошибка при порождении процесса\n");
	else if(Child == 0) {
		fprintf("Процесс-потомок: Я родился=)\n");
		fprintf("Пора на боковую\n");
		sleep(3);
		fprintf("Утро добрым не бывает...");
	}
	else if(Child > 0) {
		fprintf("Процесс-родитель");
		if(sigaction(SIGCHLD, sigact, NULL) == -1)
			fprintf("Ошибка при обработке сигнала SIGCHLD");
	}
}

void child_handler(int signum, siginfo_t *siginfo, void *context) {
	if(signum == SIGCHLD)
		fprintf("Принят сигнал SIGCHLD\n");
	else
		fprintf("Принят неопознанный сигнал: %d\n", signum);
}