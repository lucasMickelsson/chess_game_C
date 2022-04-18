#include <stdio.h>
#include "piece_functions.h"
#include "chessBoard.h"

int pawnBlackStatus[8] = {0};
int pawnWhiteStatus[8] = {0};

bool validMoves(char board[8][8], char piece, int row, int col)
{
    bool isValidMove;
    if (piece > BLACK)
    {
        piece = piece - BLACK;
        isValidMove = handlePieceFunctions(piece);
    }
    else if (isWhite(piece))
    {
        isValidMove = handlePieceFunctions(piece);
    }
    else
    {
        printf("That is not a piece\n");
        return false;
    }
}
bool handlePieceFunctions(char pieceId)
{
    switch (pieceId)
    {
    case PAWN:
        /* Function for pawn here */
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
        printf("Not a chess piece\n");
        return false;
        break;
    }
}
