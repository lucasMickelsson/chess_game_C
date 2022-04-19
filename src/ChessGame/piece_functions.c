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
        piece = piece - BLACK;
        switch (piece)
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
        }
    }
    else if (isWhite(piece))
    {
        // printf("Its a white piece\n");
        switch (piece)
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
        }
    }
    else
    {
        // printf("Its a non piece\n");
        return false;
    }
    return isValidMove;
}
