#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "chessBoard.h"

// char board[8][8];

int pawnBlackStatus[8] = {0};
int pawnWhiteStatus[8] = {0};

void initChessBoard(char board[8][8])
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
void printBoard(char board[8][8])
{
    char pieceId;
    printChessBoardLines();
    printf("\n");
    for (int i = 7; i >= 0; i--)
    {
        printf("%d|", i + 1);
        for (int j = 0; j < 8; j++)
        {
            pieceId = getPieceAtPosition(board, i, j);
            printPieceStrings(pieceId);
            if (j < 8)
            {
                printf("|");
            }
        }
        printf("\n");
        printChessBoardLines();
        printf("\n");
    }
    printf("     A       B       C       D       E       F       G       H");
}
char getPieceAtPosition(char board[8][8], int row, int col)
{
    if (row >= 0 && col >= 0 && row < 8 && col < 8)
    {
        return board[row][col];
    }
    else
    {
        return -1;
    }
}
void printPieceStrings(char pieceId)
{
    if (pieceId == EMPTY)
    {
        printf("       ");
    }
    else if (pieceId > BLACK)
    {
        pieceId = pieceId - BLACK;
        switch (pieceId)
        {
        case PAWN:
            printf(" bPawn ");
            break;

        case TOWER:
            printf(" bTower");
            break;

        case HORSE:
            printf(" bHorse");
            break;

        case BISHOP:
            printf("bBishop");
            break;

        case QUEEN:
            printf(" bQueen");
            break;

        case KING:
            printf(" bKing ");
            break;
        }
    }
    else
    {
        switch (pieceId)
        {
        case PAWN:
            printf(" wPawn ");
            break;

        case TOWER:
            printf(" wTower");
            break;

        case HORSE:
            printf(" wHorse");
            break;

        case BISHOP:
            printf("wBishop");
            break;

        case QUEEN:
            printf(" wQueen");
            break;

        case KING:
            printf(" wKing ");
            break;
        }
    }
}
void printChessBoardLines()
{
    for (int i = 0; i < 66; i++)
    {
        printf("-");
    }
}
void changeBoard(char board[8][8], int oldRow, int oldCol, int newRow, int newCol)
{
    char temp = board[oldRow][oldCol];
    board[oldRow][oldCol] = board[newRow][newCol];
    board[newRow][newCol] = temp;
}
bool positionStrings(char *chessMove)
{
    char *cheesCoord[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8",
                          "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8",
                          "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8",
                          "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8",
                          "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8",
                          "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
                          "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8",
                          "H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8"};

    for (int i = 0; i < 64; i++)
    {
        if (strcmp(chessMove, cheesCoord[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

struct chessCoord getChessCoordsIn(char *string1)
{
    struct chessCoord cord;
    char *cheesCoordinates[8][8] = {{"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8"},
                                    {"B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8"},
                                    {"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8"},
                                    {"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8"},
                                    {"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8"},
                                    {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8"},
                                    {"G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8"},
                                    {"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8"}};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (strcmp(string1, cheesCoordinates[i][j]) == 0)
            {
                cord.row = i;
                cord.col = j;
            }
        }
    }

    return cord;
}