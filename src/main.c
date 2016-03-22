#include "unixlab1.h"
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char *Mode = NULL;
int PosixNum = 0;
int SigName = 0;
pid_t SigPID = 0;

const struct option LongOptions[] = {
	{"mode", 1, 0, 0},
	{"num", 1, 0, 0},
	{"sig", 1, 0, 0},
	{"pid", 1, 0, 0}
};

int main(int argc, char *argv[]) {
	int LongI = 0;
	int opt_res = getopt_long(argc, argv, "", LongOptions, &LongI);
	while(opt_res != -1) {
		if(LongOptions[LongI].name=="mode")
			Mode = optarg;
		else if(LongOptions[LongI].name=="num")
			PosixNum = atoi(optarg);
		else if(LongOptions[LongI].name=="sig")
			SigName = atoi(optarg);
		else if(LongOptions[LongI].name=="pid")
			SigPID = atoi(optarg);
		opt_res = getopt_long(argc, argv, "", LongOptions, &LongI);
	}
	if(strcmp(Mode,"std")==0)
		run_std();
	else if(strcmp(Mode,"child")==0)
		run_child();
	else if(strcmp(Mode,"posix")==0) {
		if(PosixNum == 0)
			printf("Не задано количество сигналов POSIX --num=VALUE\n");
		else
			run_posix(PosixNum);
	}
	else if(strcmp(Mode,"kill")==0) {
		if(!SigPID || !SigName)
			printf("Не указан процесс --pid=VALUE и(или) вид сигнала --sig=VALUE\n");
		else
			run_kill(SigName, SigPID);
	}
	else if(strcmp(Mode,"pipe")==0)
		run_pipe();
	else
		printf("Неверно задан --mode=ARG\n");
	return EXIT_SUCCESS;
}