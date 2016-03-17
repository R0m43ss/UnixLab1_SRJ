#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

struct sigaction sigact;

void pipe_handler(int signum, siginfo_t *siginfo, void *context) {
	if(signum==SIGPIPE)
		printf("Принят сигнал SIGPIPE\n");
	else
		printf("Принят неопознанный сигнал\n");
}

void run_pipe() {
	sigact.sa_sigaction = &pipe_handler;
	sigact.sa_flags = SA_SIGINFO;
	int filedes[2];
	if(sigaction(SIGPIPE,&sigact,NULL)==-1) {
		perror("Ошибка обработки сигнала");
		exit(EXIT_FAILURE);
	}
	if(pipe(filedes)<0)
		perror("Ошибка при создании канала");
	else {
		pid_t Child = fork();
		if(Child < 0)
			perror("Ошибка при порождении процесса");
		else if(Child == 0) {
			close(filedes[0]);
			close(filedes[1]);
		}
		else if(Child > 0) {
			close(filedes[0]);
			sleep(2);
			write(filedes[1],"smth",4);
			int status;
			if(waitpid(-1,&status,0)<0) {
				printf("Дети-зомби атакуют!!!\n");
				exit(EXIT_FAILURE);
			}
			else exit(EXIT_SUCCESS);
		}
	} 
}