#ifndef PIECEFUNCTIONSH
#define PIECEFUNCTIONSH

#include <stdbool.h>

bool validMoves(char board[8][8], char piece, int startRow, int startCol, int moveRow, int moveCol);
bool checkPawnMoves(char board[8][8], int row, int col);

#endif