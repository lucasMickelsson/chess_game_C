# compile flag
CFLAGS = -Wall -pedantic -g
OBJ= main.o chessBoard.o

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

# Main targets

chessBoard.o: chessBoard.c chessBoard.h
	gcc $(CFLAGS) -c chessBoard.c -o chessBoard.o

main.o: main.c main.h chessBoard.h
	gcc $(CFLAGS) -c main.c -o main.o

chess$(EXEEXT): main.o chessBoard.o
	gcc $(CFLAGS) $(OBJ) -o chess

chess: chess$(EXEEXT)

all: chess$(EXEEXT) chessBoard_test$(EXEEXT) listTest$(EXEEXT)

# Test targets

listTest$(EXEEXT): pieces_list.c pieces_list.h listTest.c chessBoard.h
	gcc $(CFLAGS) pieces_list.c listTest.c -o listTest

chessBoard_test$(EXEEXT): chessBoard.o chessBoard_test.c chessBoard.h 
	gcc $(CFLAGS) chessBoard.o chessBoard_test.c -o chessBoard_test