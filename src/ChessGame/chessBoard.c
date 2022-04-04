#include <stdio.h>
#include <stdlib.h>
#include "chessBoard.h"

void initChessBoard()
{
    board[0][0] = TOWER;
    board[0][1] = HORSE;
    board[0][2] = BISHOP;
    board[0][3] = QUEEN;
    board[0][4] = KING;
    board[0][5] = BISHOP;
    board[0][6] = HORSE;
    board[0][7] = TOWER;

    for (int i = 0, x = 0; i < 8; i++, x++)
    {
        board[1][x] = PAWN;
    }
    for (int y = 2; y < 6; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            board[y][x] = EMPTY;
        }
    }
    for (int i = 0, x = 0; i < 8; i++, x++)
    {
        board[6][x] = PAWN + BLACK;
    }

    board[7][0] = TOWER + BLACK;
    board[7][1] = HORSE + BLACK;
    board[7][2] = BISHOP + BLACK;
    board[7][3] = QUEEN + BLACK;
    board[7][4] = KING + BLACK;
    board[7][5] = BISHOP + BLACK;
    board[7][6] = HORSE + BLACK;
    board[7][7] = TOWER + BLACK;
}