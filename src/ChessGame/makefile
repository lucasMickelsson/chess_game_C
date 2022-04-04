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

chess$(EXEEXT): main.c main.h
	gcc $(CFLAGS) main.c -o chess


chess: chess$(EXEEXT)

all: chess$(EXEEXT) chessBoard_test$(EXEEXT)

# Test targets

chessBoard_test$(EXEEXT): chessBoard.c chessBoard_test.c chessBoard.h 
	gcc $(CFLAGS) chessBoard.c chessBoard_test.c -o chessBoard_test