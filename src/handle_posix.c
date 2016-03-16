#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <ctime>

struct sigaction sigact;

void posix_handler(int signum, siginfo_t *siginfo, void *context) {}

void run_posix(int Num) {
	sigact.sa_sigaction = &posix_handler;
	sigact.sa_flags = SA_SIGINFO;
	pid_t Child = fork();
	if(Child < 0)
		printf(stderr,"Ошибка при порождении процесса\n");
	else if(Child == 0) {
		for(i=0;i<Num;i++) {
			printf("Child\n");
			srand(time(NULL));
			int sig = rand() % (SIGRTMAX-SIGRTMIN+1) + SIGRTMIN;
			int val = rand() % 100 + 1;
			sigqueue(getppid(),sig,val);
			printf("%i|Parent: %i|POSIX signal: %i|Value: %i\n",i,getppid(),sig,val);
		}
	}
	else if(Child > 0) {
		printf("Parent\n");
	}
}