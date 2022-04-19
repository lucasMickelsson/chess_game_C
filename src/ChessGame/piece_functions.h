#ifndef PIECEFUNCTIONSH
#define PIECEFUNCTIONSH

#include <stdbool.h>

bool validMoves(char board[8][8], char piece, int startRow, int startCol, int moveRow, int moveCol);
bool checkWhitePawnMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkBlackPawnMoves(char board[8][8], int row, int col);
bool checkForBlackPiece(char board[8][8], int row, int col);
bool checkForWhitePiece(char board[8][8], int row, int col);

#endif