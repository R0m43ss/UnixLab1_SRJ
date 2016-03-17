#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>
#include <errno.h>

void run_kill(int Signal, pid_t PID) {
	if(kill(PID, Signal)<0)
		perror("Ошибка отправки сигнала");
}