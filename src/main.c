#include "unixlab1.h"
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

char *Mode = NULL;
int PosixNum = 0;
int SigName = 0;
pid_t SigPID = 0;

const struct option LongOptions[] = {
	{"mode", 1, &Mode, optarg},
	{"num", 1, &PosixNum, atoi(optarg)},
	{"signal", 1, &SigName, atoi(optarg)},
	{"pid", 1, &SigPID, atoi(optarg)},
	{NULL, 0, NULL, 0}
}

int main(int argc, char *argv[]) {
	int opt_res = getopt_long(argc, argv, "", LongOptions, 0);
	while(opt_res != -1)
		opt_res = getopt_long(argc, argv, "", LongOptions, 0);
	if(Mode=="std")
		run_std();
	else if(Mode=="child")
		run_child();
	else if(Mode=="posix") {
		if(PosixNum == 0)
			fprintf(stderr,"Не задано количество сигналов POSIX --num=VALUE\n");
		else
			run_posix(PosixNum);
	}
	else if(Mode=="kill"){
		if(!SigPID)
			fprintf(stderr,"Не указан процесс --pid=VALUE\n");
		else if(!SigName)
			fprintf(stderr,"Не указан вид сигнала --signal=VALUE\n");
		else
			run_kill(SigName, SigPID);
	}
	else if(Mode=="pipe")
		run_pipe();
	else
		fprintf(stderr, "Неверно задан --mode=ARG\n");
	return 0;
}