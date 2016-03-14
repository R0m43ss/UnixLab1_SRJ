#include "unixlab1.h"
#include <signal.h>
#include <stdio.h>

struct sigaction sigact;
sigact.sa_sigaction = &posix_handler;
sigact.sa_flags = SA_SIGINFO;

void run_posix(int Num) {}

void posix_handler(int signum, siginfo_t *siginfo, void *context) {}