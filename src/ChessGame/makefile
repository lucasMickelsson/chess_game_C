# compile flag
CFLAGS = -Wall -pedantic -g
OBJ= main.o chessBoard.o piece_functions.o pieces_list.o king_functions.o

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

king_functions.o: king_functions.c king_functions.h chessBoard.h piece_functions.h main.h
	gcc $(CFLAGS) -c king_functions.c -o king_functions.o 

pieces_list.o: pieces_list.c pieces_list.h
	gcc $(CFLAGS) -c pieces_list.c -o pieces_list.o

piece_functions.o: piece_functions.c piece_functions.h chessBoard.h king_functions.h debug.h
	gcc $(CFLAGS) -c piece_functions.c -D DEBUGON -o piece_functions.o

chessBoard.o: chessBoard.c chessBoard.h
	gcc $(CFLAGS) -c chessBoard.c -o chessBoard.o

main.o: main.c main.h chessBoard.h piece_functions.h pieces_list.h king_functions.h debug.h
	gcc $(CFLAGS) -c main.c -D DEBUGON -o main.o

chess$(EXEEXT): main.o chessBoard.o piece_functions.o pieces_list.o king_functions.o
	gcc $(CFLAGS) $(OBJ) -D DEBUGON -o chess

chess: chess$(EXEEXT)

all: chess$(EXEEXT) chessBoard_test$(EXEEXT) listTest$(EXEEXT)

clean:
	$(RM) $(BIN) $(OBJ) $(TESTOBJ)
# Test targets

listTest$(EXEEXT): pieces_list.c pieces_list.h listTest.c chessBoard.h
	gcc $(CFLAGS) pieces_list.c listTest.c -o listTest

chessBoard_test$(EXEEXT): chessBoard.o chessBoard_test.c chessBoard.h
	gcc $(CFLAGS) chessBoard.o chessBoard_test.c -o chessBoard_test

.DEFAULT_GOAL := all