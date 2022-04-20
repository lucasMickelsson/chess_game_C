#include <stdio.h>
#include "piece_functions.h"
#include "chessBoard.h"
#include "debug.h"

int pawnBlackStatus[8] = {0};
int pawnWhiteStatus[8] = {0};

bool validMoves(char board[8][8], char piece, int startRow, int startCol, int moveRow, int moveCol)
{
    bool isValidMove = true;

    if (isBlack(piece))
    {
        if (piece == PAWN + BLACK)
        {
            isValidMove = checkBlackPawnMoves(board, startRow, startCol, moveRow, moveCol);
            return isValidMove;
        }
        else
        {
            piece = piece - BLACK;
        }
    }
    switch (piece)
    {
    case PAWN:
        isValidMove = checkWhitePawnMoves(board, startRow, startCol, moveRow, moveCol);
        break;
    case HORSE:
        /* Function for horse here */
        break;
    case QUEEN:
        /* Function for queen here */
        break;
    case KING:
        /* Function for king here */
        break;
    case BISHOP:
        /* Function for bishop here */
        break;
    case TOWER:
        /* Function for tower here */
        break;
    default:
        return false;
        break;
    }
    return isValidMove;
}
bool checkForBlackPiece(char board[8][8], int row, int col)
{
    switch (board[row][col])
    {
    case BLACK + PAWN:
    case BLACK + HORSE:
    case BLACK + QUEEN:
    case BLACK + KING:
    case BLACK + BISHOP:
    case BLACK + TOWER:
        return true;
        break;
    default:
        return false;
        break;
    }
}
bool checkForWhitePiece(char board[8][8], int row, int col)
{
    switch (board[row][col])
    {
    case PAWN:
    case HORSE:
    case QUEEN:
    case KING:
    case BISHOP:
    case TOWER:
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool checkWhitePawnMoves(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = false;

    if (pawnWhiteStatus[col] == 0) // if the pawn is in the start position
    {
        if (board[row + 2][col] == EMPTY &&
            row + 2 == moveRow && col == moveCol) // you can move to it 2 steps forward
        {
            DEBUG("2 steps forward");
            valid = true;
        }
        else if (board[row + 1][col] == EMPTY &&
                 row + 1 == moveRow && col == moveCol) // you can move to it 1 step otherwise
        {

            DEBUG("1 steps forward start");
            valid = true;
        }
        else if (checkForBlackPiece(board, row + 1, col + 1) &&
                 row + 1 == moveRow && col + 1 == moveCol) // you can knock a black piece out diagonally right
        {

            DEBUG("knock a piece out right");
            valid = true;
        }
        else if (checkForBlackPiece(board, row + 1, col - 1) &&
                 row + 1 == moveRow && col - 1 == moveCol) // also diagonally left
        {

            DEBUG("knock a piece out left");
            valid = true;
        }
        else
        {
            DEBUG("Invalid move");
            valid = false;
        }
    }
    else
    {
        if (board[row + 1][col] == EMPTY &&
            row + 1 == moveRow && col == moveCol)
        {
            DEBUG("One step no 2 step");
            valid = true;
        }
        else if (checkForBlackPiece(board, row + 1, col + 1) &&
                 row + 1 == moveRow && col + 1 == moveCol) // you can knock a black piece out diagonally right
        {
            DEBUG("knock a piece right");
            valid = true;
        }
        else if (checkForBlackPiece(board, row + 1, col - 1) &&
                 row + 1 == moveRow && col - 1 == moveCol) // also diagonally left
        {
            DEBUG("knock piece left");
            valid = true;
        }
        else
        {
            DEBUG("Invalid");
            valid = false;
        }
    }
    if (valid)
    {
        pawnWhiteStatus[col]++;
    }

    return valid;
}
bool checkBlackPawnMoves(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = false;

    if (pawnBlackStatus[col] == 0) // if the pawn is in the start position
    {
        if (board[row - 2][col] == EMPTY &&
            row - 2 == moveRow && col == moveCol) // you can move to it 2 steps forward
        {
            valid = true;
        }
        else if (board[row - 1][col] == EMPTY &&
                 row - 1 == moveRow && col == moveCol) // you can move to it 1 step otherwise
        {
            valid = true;
        }
        else if (checkForBlackPiece(board, row - 1, col - 1) &&
                 row - 1 == moveRow && col - 1 == moveCol) // you can knock a black piece out diagonally right
        {
            valid = true;
        }
        else if (checkForBlackPiece(board, row - 1, col + 1) &&
                 row - 1 == moveRow && col + 1 == moveCol) // also diagonally left
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        if (board[row - 1][col] == EMPTY &&
            row - 1 == moveRow && col == moveCol)
        {
            valid = true;
        }
        else if (checkForWhitePiece(board, row - 1, col - 1) &&
                 row - 1 == moveRow && col - 1 == moveCol) // you can knock a black piece out diagonally right
        {
            valid = true;
        }
        else if (checkForWhitePiece(board, row - 1, col + 1) &&
                 row - 1 == moveRow && col + 1 == moveCol) // also diagonally left
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    if (valid)
    {
        pawnBlackStatus[col]++;
    }

    return valid;
}
