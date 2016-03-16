#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <ctime>

struct sigaction sigact;
int coiunt=0;

void posix_handler(int signum, siginfo_t *siginfo, void *context) {
	printf("Parent: %i|PID=%i|Parent=%i|POSIX signal=%i|Value=%i\n",count,getpid(),getppid(),signum,siginfo->si_value.sival_int);
	count++;
}

void run_posix(int Num) {
	sigact.sa_sigaction = &posix_handler;
	sigact.sa_flags = SA_SIGINFO;
	int j=0;
	for(j=SIGRTMIN;j<SIGRTMAX+1;j++) {
		if(sigaction(j,&sigact,NULL)==-1)
			printf("Ошибка обработки сигнала %i\n",j);
	}
	pid_t Child = fork();
	if(Child < 0)
		printf(stderr,"Ошибка при порождении процесса\n");
	else if(Child == 0) {
		int i=0;
		printf("Потомок\n");
		for(i=0;i<Num;i++) {
			srand(i*3);
			int sig = rand() % (SIGRTMAX-SIGRTMIN+1) + SIGRTMIN;
			union sigval val;
			val.sival_int = rand();
			sigqueue(getppid(),sig,val);
			printf("Child: %i|PID=%i|Parent=%i|POSIX signal=%i|Value=%i\n",i,getpid(),getppid(),sig,val.sival_int);
		}
	}
	else if(Child > 0) {
		printf("Родитель\n");
		sleep(30);
		int status;
		if(wait(&status)<0)
			printf("Дети-зомби атакуют!!!\n");
	}
}