#ifndef CHESSBOARDH
#define CHESSBOARDH
#include <stdbool.h>
#include "pieces_list.h"

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

struct coord
{
    int row;
    int col;
};

/**
 * Function for building and initialize every position to a piece
 */
void initChessBoard(char board[8][8]);

/**
 * Function for printing the board on the screen
 */
void printBoard(char board[8][8], a_piece *head);

/**
 * @brief Get the Piece At Position on the chess board
 *
 * @param board chess board array
 * @param row
 * @param col
 * @return the pieceid back
 */
char getPieceAtPosition(char board[8][8], int row, int col);

void setPieceAtPosition(char board[8][8], char pieceId, int row, int col);

/**
 * Function for printing a pieceString on the board
 *
 * @param pieceid id for the piece to be printed
 */
void printPieceStrings(char pieceId);

/**
 * Function for printing lines for chessboard
 */
void printChessBoardLines();

/**
 * Function for changing position between to pieces
 * @param board
 * @param oldRow
 * @param oldCol
 * @param newRow
 * @param newCol
 */
a_piece *changeBoard(char board[8][8], int oldRow, int oldCol, int newRow, int newCol, a_piece *head);

/**
 * Function for checking if a string is a chess coordinate
 * @param chessMove
 * @return true if its valid false otherwise
 */
bool positionStrings(char *chessMove);

/**
 * @brief Get the chess coordinates for a chess move for example A1= 0 0
 *
 * @param string1 the chessmove example B2 A4 B6
 * @return struct with 2 integer for col and row
 */
struct coord getChessIndex(char *string1);

bool isWhite(char pieceId);
bool isBlack(char pieceId);
void copyBoard(char oldBoard[8][8], char aCopy[8][8]);
int countPiecesOnBoard(char board[8][8]);
void initPawnChessboard(char board[8][8]);
void swap(char board[8][8], int oldRow, int oldCol, int newRow, int newCol);

#endif