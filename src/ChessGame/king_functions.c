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
            if (pieceStart == KING + color)
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
                        setPieceAtPosition(board, pieceStart, p1.row, p1.col);
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
        return !blackPieceIsSafe(board, row, col);
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
        return !whitePieceIsSafe(board, row, col);
    }
}

bool whitePieceIsSafe(char board[8][8], int row, int col)
{
    int i, j;
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
        // Checking diagonals
        // Checking diagonal upper right
        for (int i = row + 1, j = col + 1; i <= 7 && j <= 7; i++, j++)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + BISHOP ||
                         (piece == BLACK + KING && i - row == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking diagonal upper left
        for (int i = row + 1, j = col - 1; i <= 7 && j >= 0; i++, j--)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + BISHOP ||
                         (piece == BLACK + KING && i - row == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking diagonal lower left
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + BISHOP ||
                         (piece == BLACK + KING && row - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking diagonal lower right
        for (int i = row - 1, j = col + 1; i >= 0 && j <= 7; i--, j++)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + BISHOP ||
                         (piece == BLACK + KING && row - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking horizontally and vertically
        // Checking right
        for (int i = col + 1; i <= 7; i++)
        {
            char piece = getPieceAtPosition(board, row, i);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + TOWER ||
                         (piece == BLACK + KING && i - col == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking left
        for (int i = col - 1; i >= 0; i--)
        {
            char piece = getPieceAtPosition(board, row, i);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + TOWER ||
                         (piece == BLACK + KING && col - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking up
        for (int i = row + 1; i <= 7; i++)
        {
            char piece = getPieceAtPosition(board, i, col);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + TOWER ||
                         (piece == BLACK + KING && i - row == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking down
        for (int i = row - 1; i >= 0; i--)
        {
            char piece = getPieceAtPosition(board, i, col);
            if (piece != EMPTY)
            {
                if (isWhite(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == BLACK + QUEEN || piece == BLACK + TOWER ||
                         (piece == BLACK + KING && row - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Check for horses
        // up
        i = row + 2;
        if (i <= 7)
        {
            // Left
            j = col - 1;
            if (j >= 0)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = col + 1;
            if (j <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
        }

        // down
        i = row - 2;
        if (i >= 0)
        {
            // Left
            j = col - 1;
            if (j >= 0)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = col + 1;
            if (j <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
        }

        // right
        j = col + 2;
        if (j >= 0)
        {
            // Left
            i = row + 1;
            if (i <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = row - 1;
            if (j >= 0)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
        }
        // left
        j = col - 2;
        if (j >= 0)
        {
            // Left
            i = row - 1;
            if (i <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = row + 1;
            if (j <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == BLACK + HORSE)
                    {
                        return false;
                    }
                }
            }
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
bool blackPieceIsSafe(char board[8][8], int row, int col)
{
    int i, j;
    if (isBlack(getPieceAtPosition(board, row, col)))
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
        // Checking diagonals
        // Checking diagonal upper right
        for (int i = row + 1, j = col + 1; i <= 7 && j <= 7; i++, j++)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == BISHOP ||
                         (piece == KING && i - row == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking diagonal upper left
        for (int i = row + 1, j = col - 1; i <= 7 && j >= 0; i++, j--)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == BISHOP ||
                         (piece == KING && i - row == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking diagonal lower left
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == BISHOP ||
                         (piece == KING && row - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking diagonal lower right
        for (int i = row - 1, j = col + 1; i >= 0 && j <= 7; i--, j++)
        {
            char piece = getPieceAtPosition(board, i, j);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == BISHOP ||
                         (piece == KING && row - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking horizontally and vertically
        // Checking right
        for (int i = col + 1; i <= 7; i++)
        {
            char piece = getPieceAtPosition(board, row, i);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == TOWER ||
                         (piece == KING && i - col == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking left
        for (int i = col - 1; i >= 0; i--)
        {
            char piece = getPieceAtPosition(board, row, i);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == TOWER ||
                         (piece == KING && col - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking up
        for (int i = row + 1; i <= 7; i++)
        {
            char piece = getPieceAtPosition(board, i, col);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == TOWER ||
                         (piece == KING && i - row == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Checking down
        for (int i = row - 1; i >= 0; i--)
        {
            char piece = getPieceAtPosition(board, i, col);
            if (piece != EMPTY)
            {
                if (isBlack(piece)) // Friendly piece
                {
                    break;
                }
                else if (piece == QUEEN || piece == TOWER ||
                         (piece == KING && row - i == 1))
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }
        // Check for horses
        // up
        i = row + 2;
        if (i <= 7)
        {
            // Left
            j = col - 1;
            if (j >= 0)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = col + 1;
            if (j <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
        }

        // down
        i = row - 2;
        if (i >= 0)
        {
            // Left
            j = col - 1;
            if (j >= 0)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = col + 1;
            if (j <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
        }

        // right
        j = col + 2;
        if (j >= 0)
        {
            // Left
            i = row + 1;
            if (i <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = row - 1;
            if (j >= 0)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
        }
        // left
        j = col - 2;
        if (j >= 0)
        {
            // Left
            i = row - 1;
            if (i <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
            // Right
            j = row + 1;
            if (j <= 7)
            {
                char piece = getPieceAtPosition(board, i, j);
                if (piece != EMPTY)
                {
                    if (piece == HORSE)
                    {
                        return false;
                    }
                }
            }
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

bool checkMate(char board[8][8], int color)
{
    /*Checkmate will happen if king is threated and the player can not block it and not
    knock the piece out*/
    if (isBlack(color))
    {
        /* code */
    }
    else
    {
    }
}