#ifndef __UNIXLAB__
#define __UNIXLAB__
#include <signal.h>

void run_std();
void run_child();
void run_posix(int Num);
void run_kill(int Signal, pid_t PID);
void run_pipe();

void std_handler(int signum, siginfo_t *siginfo, void *context);
void child_handler(int signum, siginfo_t *siginfo, void *context);
void posix_handler(int signum, siginfo_t *siginfo, void *context);
void pipe_handler(int signum, siginfo_t *siginfo, void *context);

#endif