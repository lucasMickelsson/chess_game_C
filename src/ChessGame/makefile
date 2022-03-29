# compile flag
CFLAGS = -Wall -pedantic -g

# operating system dependent variables
ifeq ($(OS), Windows_NT)
RM = del
BIN = chess.exe
EXEEXT = .exe
else
RM = rm
BIN = chess
EXEEXT = 
endif

# Targets

chess$(EXEEXT): main.c
	gcc $(CFLAGS) main.c -o chess