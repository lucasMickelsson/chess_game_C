#include <stdio.h>
#include "piece_functions.h"
#include "chessBoard.h"

int pawnBlackStatus[8] = {0};
int pawnWhiteStatus[8] = {0};

bool validMoves(char board[8][8], char piece, int startRow, int startCol, int moveRow, int moveCol)
{
    bool isValidMove = true;

    if (piece > BLACK)
    {
        // printf("Its a black piece\n");
        if (piece == PAWN + BLACK)
        {
            piece = piece - BLACK;
            /* Function for black pawn here with return value afterwards*/
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
    pawnWhiteStatus[col]++;

    if (pawnWhiteStatus[col] == 1) // if the pawn is in the start position
    {
        if (board[row + 2][col] == EMPTY &&
            board[row + 2][col] == board[moveRow][moveCol]) // you can move to it 2 steps forward
        {
            valid = true;
        }
        if (board[row + 1][col] == EMPTY &&
            board[row + 1][col] == board[moveRow][moveCol]) // you can move to it 1 step otherwise
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
        if (board[row + 1][col] == EMPTY &&
            board[row + 1][col] == board[moveRow][moveCol])
        {
            valid = true;
        }
        if (checkForBlackPiece(board, row + 1, col + 1) &&
            board[row + 1][col + 1] == board[moveRow][moveCol]) // you can knock a black piece out diagonally right
        {
            valid = true;
        }
        if (checkForBlackPiece(board, row + 1, col - 1) &&
            board[row + 1][col - 1] == board[moveRow][moveCol]) // also diagonally left
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    return valid;
}
bool checkBlackPawnMoves(char board[8][8], int row, int col)
{
}
