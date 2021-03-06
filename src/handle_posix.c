#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

struct sigaction sigact;
int count=0;

void posix_handler(int signum, siginfo_t *siginfo, void *context) {
	printf("Parent: %i|PID=%i|Parent=%i|POSIX signal=%i|Value=%i\n",count+1,getpid(),getppid(),signum,siginfo->si_value.sival_int);
	count++;
}

void run_posix(int Num) {
	sigact.sa_sigaction = &posix_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigset_t sigset;
	if(sigfillset(&sigset)<0) {
		perror("Ошибка sigfillset");
		exit(EXIT_FAILURE);
	}
	if(sigprocmask(SIG_BLOCK, &sigset, NULL)<0) {
		perror("Ошибка sigprocmask");
		exit(EXIT_FAILURE);
	}
	int j=0;
	for(j=SIGRTMIN;j<SIGRTMAX+1;j++) {
		if(sigaction(j,&sigact,NULL)==-1) {
			perror("Ошибка при обработке POSIX сигнала");
			exit(EXIT_FAILURE);
		}
	}
	pid_t Child = fork();
	if(Child < 0)
		perror("Ошибка при порождении процесса");
	else if(Child == 0) {
		int i=0;
		for(i=0;i<Num;i++) {
			srand(i*3);
			int sig = rand() % (SIGRTMAX-SIGRTMIN+1) + SIGRTMIN;
			union sigval val;
			val.sival_int = rand();
			if(sigqueue(getppid(),sig,val)<0) {
				perror("Ошибка при отправке сигнала");
				exit(EXIT_FAILURE);
			}
			printf("Child: %i|PID=%i|Parent=%i|POSIX signal=%i|Value=%i\n",i+1,getpid(),getppid(),sig,val.sival_int);
		}
	}
	else if(Child > 0) {
		int status;
		if(waitpid(-1,&status,0)<0) {
			printf("Дети-зомби атакуют!!!\n");
			exit(EXIT_FAILURE);
		}
		else {
			if(sigprocmask(SIG_UNBLOCK, &sigset, NULL)<0) {
				perror("Ошибка sigprocmask");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
	}
}