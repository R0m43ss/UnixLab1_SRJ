#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

struct sigaction sigact;

void std_handler(int signum, siginfo_t *siginfo, void *context) {
	char *sig_name = NULL;
	if(signum == SIGUSR1)
		sig_name = "SIGUSR1";
	else if(signum == SIGUSR2)
		sig_name = "SIGUSR2";
	else if(signum == SIGHUP)
		sig_name = "SIGHUP";
	if(sig_name == NULL)
		printf("Принят неопознанный сигнал: %d\n", signum);
	else
		printf("Принят сигнал %s, PID = %i, GID = %i\n", sig_name, siginfo->si_pid, getpgid(siginfo->si_pid));
}

void run_std() {
	sigact.sa_sigaction = &std_handler;
	sigact.sa_flags = SA_SIGINFO;
	if(sigaction(SIGUSR1, &sigact, NULL) == -1) {
		perror("Ошибка при обработке сигнала SIGUSR1");
		exit(EXIT_FAILURE);
	}
	if(sigaction(SIGUSR2, &sigact, NULL) == -1) {
		perror("Ошибка при обработке сигнала SIGUSR2");
		exit(EXIT_FAILURE);
	}
	if(sigaction(SIGHUP, &sigact, NULL) == -1) {
		perror("Ошибка при обработке сигнала SIGHUP");
		exit(EXIT_FAILURE);
	}
	/*sleep(2);
	raise(SIGUSR1);
	sleep(2);
	raise(SIGUSR2);
	sleep(2);
	raise(SIGHUP);*/
	while(1) {
		sleep(1); 
	}
}