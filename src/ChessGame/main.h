#ifndef MAINH
#define MAINH
#include <stdbool.h>
#include "pieces_list.h"

void printLines(void);
void clear_buffer();
int user_selection();
void printChessModeOptions();
void handleChessOptions();
bool playComputerOrNot();
void printLogo(void);
void printWelcomeMessage(void);
void printStart(void);
void printMenyOptions();
void clear_buffer();
void print2PlayerModeInfo();
void printPawnChessInfo();
void confirm();
void chessGameGo(int chessMode);
void readString(char array[], int size);
int player1(char board[8][8]);
int player2(char board[8][8]);
bool equalStrings(char *string1, char *string2);
void clearScreen(void);

#endif
