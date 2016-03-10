INC=./includes
SRC=./src
OUT=./bin

$(OUT)/lab: $(OUT)/main.o $(OUT)/handle_standard.o $(OUT)/handle_sigchld.o $(OUT)/handle_posix.o $(OUT)/send_kill.o $(OUT)/handle_pipe.o
	gcc -o $(OUT)/lab $(OUT)/main.o $(OUT)/handle_standard.o $(OUT)/handle_sigchld.o $(OUT)/handle_posix.o $(OUT)/send_kill.o $(OUT)/handle_pipe.o
	
$(OUT)/main.o: $(SRC)/main.c $(INC)/unixlab1.h
	gcc -I$(INC) -o $(OUT)/main.o -c $(SRC)/main.c

$(OUT)/handle_standard.o: $(SRC)/handle_standard.c $(INC)/unixlab1.h
	gcc -I$(INC) -o $(OUT)/handle_standard.o -c $(SRC)/handle_standard.c

$(OUT)/handle_sigchld.o: $(SRC)/handle_sigchld.c $(INC)/unixlab1.h
	gcc -I$(INC) -o $(OUT)/handle_sigchld.o -c $(SRC)/handle_sigchld.c

$(OUT)/handle_posix.o: $(SRC)/handle_posix.c $(INC)/unixlab1.h
	gcc -I$(INC) -o $(OUT)/handle_posix.o -c $(SRC)/handle_posix.c

$(OUT)/send_kill.o: $(SRC)/send_kill.c $(INC)/unixlab1.h
	gcc -I$(INC) -o $(OUT)/send_kill.o -c $(SRC)/send_kill.c

$(OUT)/handle_pipe.o: $(SRC)/handle_pipe.c $(INC)/unixlab1.h
	gcc -I$(INC) -o $(OUT)/handle_pipe.o -c $(SRC)/handle_pipe.c

clean:
	rm $(OUT)/*.o $(OUT)/lab