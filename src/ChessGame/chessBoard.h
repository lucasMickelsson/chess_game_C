#ifndef CHESSBOARDH
#define CHESSBOARDH

// every chess piece has been given an unique id
#define EMPTY 0
#define BLACK 50
#define WHITE 0
#define PAWN 1
#define HORSE 3
#define BISHOP 4
#define ROOK 2
#define QUEEN 5
#define KING 6

/**
 * Function for building and initizliaze every position to a piece
 * @return the new board
 */
char *buildChessBoard();

/**
 * Function for printing the board on the screen
 * @param the board for now
 */
void printBoard(char *board);

#endif