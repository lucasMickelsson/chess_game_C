#ifndef KINGFUNCTIONSH
#define KINGFUNCTIONSH

bool kingInCheck(char board[8][8], char colorKing);
bool checkWhiteKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkBlackKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
int moveThreatedKing(char board[8][8], char color, char player);
bool whitePieceIsSafe(char board[8][8], int row, int col);
bool blackPieceIsSafe(char board[8][8], int row, int col);
bool checkMate(char board[8][8], int color);
struct coord findPiece(char board[8][8], char color, char piece);
bool kingIsCheckInMove(char board[8][8], int row, int col, int color, int moveRow, int moveCol);
bool gameEndsIndraw(char board[8][8]);
bool checkForAnyLegalMove(char board[8][8], char color);
bool checkValidRockedMove(char board[8][8], int row, int col, int color, int moveRow, int moveCol);

#endif