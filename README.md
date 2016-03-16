# UnixLab1_SRJ
Program for Unix signal handlings.

How to:
- Assemble: make
- Clean: make clean
- Launch: ./bin/lab
	- for standard signals: --mode=std
	- for SIGCHLD: --mode=child
	- for POSIX signals: --mode=posix --num=VALUE
	- for sending signals: --mode=kill --sig=VALUE --pid=VALUE
	- for SIGPIPE: --mode=pipe