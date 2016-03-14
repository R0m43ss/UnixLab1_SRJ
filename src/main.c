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
	switch(Mode) {
		case "std":
			run_std();
			break;
		case "child":
			run_child();
			break;
		case "posix":
			if(PosixNum == 0) {
				fprintf(stderr,"Не задано количество сигналов POSIX --num=VALUE\n");
				break;
			}
			run_posix(PosixNum);
			break;
		case "kill":
			if(!SigPID) {
				fprintf(stderr,"Не указан процесс --pid=VALUE\n");
				break;
			}
			if(!SigName) {
				fprintf(stderr,"Не указан вид сигнала --signal=VALUE\n");
				break;
			}
			run_kill(SigName, SigPID);
			break;
		case "pipe":
			run_pipe();
			break;
		default:
			fprintf(stderr, "Неверно задан --mode=ARG\n");
			break;
	}
	return 0;
}