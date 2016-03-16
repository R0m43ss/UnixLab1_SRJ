#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>

struct sigaction sigact;

void pipe_handler(int signum, siginfo_t *siginfo, void *context) {
	if(signum==SIGPIPE)
		printf("Принят сигнал SIGPIPE");
	else
		printf("Принят неопознанный сигнал");
}

void run_pipe() {
	sigact.sa_sigaction = &pipe_handler;
	sigact.sa_flags = SA_SIGINFO;
}