#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>

void run_kill(int Signal, pid_t PID) {
	kill(PID, Signal);
	printf("Процессу %i был послан сигнал %i\n", PID, Signal);
}