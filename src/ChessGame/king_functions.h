#ifndef KINGFUNCTIONSH
#define KINGFUNCTIONSH

bool kingInCheck(char board[8][8], char colorKing);
bool kingIsSafe(char board[8][8], int row, int col);
bool checkWhiteKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkBlackKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
int moveThreatedKing(char board[8][8], char color, char player);
bool whiteKingIsSafe(char board[8][8], int row, int col);
bool blackKingIsSafe(char board[8][8], int row, int col);

#endif