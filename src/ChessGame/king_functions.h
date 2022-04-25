#ifndef KINGFUNCTIONSH
#define KINGFUNCTIONSH

bool kingInCheck(char board[8][8], char colorKing);
bool kingIsSafe(char board[8][8], int row, int col);
bool checkWhiteKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkBlackKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol);

#endif