#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>

struct sigaction sigact;
sigact.sa_sigaction = &pipe_handler;
sigact.sa_flags = SA_SIGINFO;

void run_pipe() {}

void pipe_handler(int signum, siginfo_t *siginfo, void *context) {
	if(signum==SIGPIPE)
		fprintf("Принят сигнал SIGPIPE");
	else
		fprintf("Принят неопознанный сигнал");
}