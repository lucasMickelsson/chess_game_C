#ifndef CHESSBOARDH
#define CHESSBOARDH

// every chess piece has been given an unique id
// black pieces will have id defined= pieceID + 50
#define BLACK 50
#define WHITE 0
#define EMPTY 0

#define PAWN 1
#define TOWER 2
#define HORSE 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

char board[8][8];

/**
 * Function for building and initialize every position to a piece
 */
void initChessBoard();

/**
 * Function for printing the board on the screen
 */
void printBoard();

#endif