#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "king_functions.h"
#include "chessBoard.h"
#include "piece_functions.h"
#include "main.h"

int moveThreatedKing(char board[8][8], char color, char player)
{
    char command[10];
    char *end, *start;
    bool valid = false;
    struct coord p1, p2;

    printf("\nPlayer %d Save the king! ", player);
    do
    {
        readString(command, 10);
        if (strcmp(command, "quit") == 0)
        {
            return -1;
        }
        start = strtok(command, " ");
        end = strtok(NULL, " ");

        if (start == NULL || end == NULL)
        {
            printf("Invalid input for chess move try again in this format(startPos endPos): ");
        }
        else if (positionStrings(start) && positionStrings(end))
        {
            p1 = getChessIndex(start);
            p2 = getChessIndex(end);
            // printf("Coors are %d %d\n", p1.row, p1.col);
            char pieceStart = getPieceAtPosition(board, p1.row, p1.col);
            if (pieceStart == KING)
            {
                char Oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                valid = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                if (!valid)
                {
                    printf("The chess move is invalid, try again: ");
                }
                else
                {
                    changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                    if (kingInCheck(board, color))
                    {
                        printf("The king will enter a square where it get threated, invalid!\n");
                        setPieceAtPosition(board, color + KING, p1.row, p1.col);
                        setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                        moveThreatedKing(board, color, player);
                    }
                }
            }
            else if (pieceStart != color + KING)
            {
                char oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                valid = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                if (!valid)
                {
                    printf("The chess move is invalid, try again: ");
                }
                else
                {
                    changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                    if (kingInCheck(board, color))
                    {
                        printf("The king is still in danger. Save it!\n");
                        setPieceAtPosition(board, color + KING, p1.row, p1.col);
                        setPieceAtPosition(board, oldpiece, p2.row, p2.col);
                        moveThreatedKing(board, color, player);
                    }
                }
            }
            else
            {
                printf("You have to protect the king away from danger: ");
            }
        }
    } while (!valid);

    return valid;
}

bool kingInCheck(char board[8][8], char colorKing)
{
    int row, col;
    if (isBlack(colorKing))
    {
        // Find the black king
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPieceAtPosition(board, i, j) == KING + BLACK)
                {
                    row = i;
                    col = j;
                }
            }
        }
        return !kingIsSafe(board, row, col);
    }
    else
    {
        // Find the white king
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPieceAtPosition(board, i, j) == KING)
                {
                    row = i;
                    col = j;
                }
            }
        }
        return !kingIsSafe(board, row, col);
    }
}

bool kingIsSafe(char board[8][8], int row, int col)
{
    if (isWhite(getPieceAtPosition(board, row, col)))
    {
        // Check for black pawns
        if (row + 1 <= 7 && col - 1 >= 0 && getPieceAtPosition(board, row + 1, col - 1) == PAWN + BLACK)
        {
            return false;
        }
        else if (row + 1 <= 7 && col + 1 <= 7 && getPieceAtPosition(board, row + 1, col + 1) == PAWN + BLACK)
        {
            return false;
        }
        // Check for horses
        // Check for Bishops
        // Check for Queens
        // Check for towers
        // Check for king

        // No threats founded
        return true;
    }
    else if (isBlack(getPieceAtPosition(board, row, col)))
    {
        // Check for white pawns
        if (row - 1 >= 0 && col - 1 >= 0 && getPieceAtPosition(board, row - 1, col - 1) == PAWN)
        {
            return false;
        }
        else if (row - 1 >= 0 && col + 1 <= 7 && getPieceAtPosition(board, row - 1, col + 1) == PAWN)
        {
            return false;
        }

        // No threats founded
        return true;
    }
    else
    {
        // empty square
        return true;
    }
}

bool checkWhiteKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = false;
    // Notation: We also need to check if the position of the move is safe for the king
    if ((board[row + 1][col] == EMPTY && row + 1 == moveRow && col == moveCol) ||
        (checkForBlackPiece(board, row + 1, col) && row + 1 == moveRow && col == moveCol))
    {
        valid = true;
    }
    else if ((board[row + 1][col + 1] == EMPTY && row + 1 == moveRow && col + 1 == moveCol) ||
             (checkForBlackPiece(board, row + 1, col + 1) && row + 1 == moveRow && col + 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row][col + 1] == EMPTY && row == moveRow && col + 1 == moveCol) ||
             (checkForBlackPiece(board, row, col + 1) && row == moveRow && col + 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row - 1][col + 1] == EMPTY && row - 1 == moveRow && col + 1 == moveCol) ||
             (checkForBlackPiece(board, row - 1, col + 1) && row - 1 == moveRow && col + 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row - 1][col] == EMPTY && row - 1 == moveRow && col == moveCol) ||
             (checkForBlackPiece(board, row - 1, col) && row - 1 == moveRow && col == moveCol))
    {
        valid = true;
    }
    else if ((board[row - 1][col - 1] == EMPTY && row - 1 == moveRow && col - 1 == moveCol) ||
             (checkForBlackPiece(board, row - 1, col - 1) && row - 1 == moveRow && col - 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row][col - 1] == EMPTY && row == moveRow && col - 1 == moveCol) ||
             (checkForBlackPiece(board, row, col - 1) && row == moveRow && col - 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row + 1][col - 1] == EMPTY && row + 1 == moveRow && col - 1 == moveCol) ||
             (checkForBlackPiece(board, row + 1, col - 1) && row + 1 == moveRow && col - 1 == moveCol))
    {
        valid = true;
    }
    else
    {
        valid = false;
    }
    return valid;
}
bool checkBlackKingMoves(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = false;
    // Notation: We also need to check if the position of the move is safe for the king
    if ((board[row + 1][col] == EMPTY && row + 1 == moveRow && col == moveCol) ||
        (checkForWhitePiece(board, row + 1, col) && row + 1 == moveRow && col == moveCol))
    {
        valid = true;
    }
    else if ((board[row + 1][col + 1] == EMPTY && row + 1 == moveRow && col + 1 == moveCol) ||
             (checkForWhitePiece(board, row + 1, col + 1) && row + 1 == moveRow && col + 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row][col + 1] == EMPTY && row == moveRow && col + 1 == moveCol) ||
             (checkForWhitePiece(board, row, col + 1) && row == moveRow && col + 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row - 1][col + 1] == EMPTY && row - 1 == moveRow && col + 1 == moveCol) ||
             (checkForWhitePiece(board, row - 1, col + 1) && row - 1 == moveRow && col + 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row - 1][col] == EMPTY && row - 1 == moveRow && col == moveCol) ||
             (checkForWhitePiece(board, row - 1, col) && row - 1 == moveRow && col == moveCol))
    {
        valid = true;
    }
    else if ((board[row - 1][col - 1] == EMPTY && row - 1 == moveRow && col - 1 == moveCol) ||
             (checkForWhitePiece(board, row - 1, col - 1) && row - 1 == moveRow && col - 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row][col - 1] == EMPTY && row == moveRow && col - 1 == moveCol) ||
             (checkForWhitePiece(board, row, col - 1) && row == moveRow && col - 1 == moveCol))
    {
        valid = true;
    }
    else if ((board[row + 1][col - 1] == EMPTY && row + 1 == moveRow && col - 1 == moveCol) ||
             (checkForWhitePiece(board, row + 1, col - 1) && row + 1 == moveRow && col - 1 == moveCol))
    {
        valid = true;
    }
    else
    {
        valid = false;
    }
    return valid;
}