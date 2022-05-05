#ifndef PIECEFUNCTIONSH
#define PIECEFUNCTIONSH

#include <stdbool.h>

/**
 * Function for checking a move from user for a specific piece
 * @param board the chessboard
 * @param piece the piece to be moved and checked
 * @param startRow
 * @param startCol
 * @param moveRow end row postition for the move
 * @param moveCol end column postition for the move
 * @return true if its a valid move false otherwise
 */
bool validMoves(char board[8][8], char piece, int startRow, int startCol, int moveRow, int moveCol);

/**
 * Function for checking a move for a white pawn
 * @param board chessboard
 * @param row start row position
 * @param col start column position
 * @param moveRow end row position
 * @param moveCol end column position
 * @return true if the move of the white pawn is valid false otherwise
 */
bool checkWhitePawnMoves(char board[8][8], int row, int col, int moveRow, int moveCol);

/**
 * Function for checking a move for a black pawn
 * @param board chessboard
 * @param row start row position
 * @param col start column position
 * @param moveRow end row position
 * @param moveCol end column position
 * @return true if the move of the black pawn is valid false otherwise
 */
bool checkBlackPawnMoves(char board[8][8], int row, int col, int moveRow, int moveCol);

/**
 * Function for checking if it exist a black piece at a given position
 * @param board chessboard
 * @param row row position
 * @param col column position
 * @return true if a black piece was finded false otherwise
 */
bool checkForBlackPiece(char board[8][8], int row, int col);

/**
 * Function for checking if it exist a white piece at a given position
 * @param board chessboard
 * @param row row position
 * @param col column position
 * @return true if a white piece was finded false otherwise
 */
bool checkForWhitePiece(char board[8][8], int row, int col);

/**
 * Function for checking moves of chess piece tower
 * @param board chessboard
 * @param row startrow of the tower
 * @param col startcolumn of the tower
 * @param moveRow the move row of the tower
 * @param moveCol the move column of the tower
 * @return true if the move of the tower is valid false otherwise
 */
bool checkTowerMoves(char board[8][8], int row, int col, int moveRow, int moveCol);

/**
 * Function for checking positions horizontally of the chessboard where a chess move is given
 * @param board chessboard
 * @param row startrow of the piece
 * @param col startcolumn of the piece
 * @param moveRow the move row of the piece
 * @param moveCol the move column of the piece
 * @return true if the move of the specific piece horizontally is valid false otherwise
 */
bool horizontallyCheck(char board[8][8], int row, int col, int moveRow, int moveCol);

/**
 * Function for checking positions vertically of the chessboard where a chess move is given
 * @param board chessboard
 * @param row startrow of the piece
 * @param col startcolumn of the piece
 * @param moveRow the move row of the piece
 * @param moveCol the move column of the piece
 * @return true if the move of the specific piece vertically is valid false otherwise
 */
bool verticallyCheck(char board[8][8], int row, int col, int moveRow, int moveCol);

/**
 * @brief
 *
 * @param board
 * @param row
 * @param col
 * @param moveRow
 * @param moveCol
 * @return true
 * @return false
 */
bool checkBishopMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool diagonallyCheck(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkQueenMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkWhiteHorseMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool checkBlackHorseMoves(char board[8][8], int row, int col, int moveRow, int moveCol);
bool kingInCheck(char board[8][8], char colorKing);
void makeRockMove(char board[8][8], int color, int row, int col, int moveRow, int moveCol);

#endif