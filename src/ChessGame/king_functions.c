#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "king_functions.h"
#include "chessBoard.h"
#include "piece_functions.h"
#include "main.h"

int kingStatusBlack = 0, kingStatusWhite = 0, towerWhiteStatus = 0, towerBlackStatus = 0;

bool kingIsCheckInMove(char board[8][8], int row, int col, int color, int moveRow, int moveCol)
{
    char tempBoard[8][8];
    copyBoard(board, tempBoard);
    changeBoard(tempBoard, row, col, moveRow, moveCol); // Make the planning move and check for threat
    if (kingInCheck(tempBoard, color))
    {
        return true;
    }
    else
    {
        return false;
    }
}
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
            char pieceStart = getPieceAtPosition(board, p1.row, p1.col);
            if (pieceStart == KING + color)
            {
                valid = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                if (!valid)
                {
                    printf("The chess move is invalid, try again: ");
                }
                else
                {
                    if (kingIsCheckInMove(board, p1.row, p1.col, color, p2.row, p2.col))
                    {
                        printf("The king is still in danger after that move\n");
                        moveThreatedKing(board, color, player);
                    }
                    else
                    {
                        changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                    }
                }
            }
            else if (pieceStart != color + KING)
            {
                valid = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                if (!valid)
                {
                    printf("The chess move is invalid, try again: ");
                }
                else
                {
                    if (kingIsCheckInMove(board, p1.row, p1.col, color, p2.row, p2.col))
                    {
                        printf("The king is still in danger after that move\n");
                        moveThreatedKing(board, color, player);
                    }
                    else
                    {
                        changeBoard(board, p1.row, p1.col, p2.row, p2.col);
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
    struct coord kingPos;
    if (isBlack(colorKing))
    {
        kingPos = findPiece(board, BLACK, KING);
        return !blackPieceIsSafe(board, kingPos.row, kingPos.col);
    }
    else
    {
        kingPos = findPiece(board, WHITE, KING);
        return !whitePieceIsSafe(board, kingPos.row, kingPos.col);
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
        // Checking diagonals (Bishop, Queen, King)
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
bool checkValidRockedMove(char board[8][8], int row, int col, int color, int moveRow, int moveCol)
{
    if (isBlack(color))
    {
        if (!kingInCheck(board, color) && kingStatusBlack == 0 &&
            board[row][col] == KING + BLACK && row == 7 && col == 4)
        {
            if (board[row][col + 1] == EMPTY && board[row][col + 2] == EMPTY &&
                board[row][col + 3] == BLACK + TOWER)
            {
                if (!kingIsCheckInMove(board, row, col, BLACK, row, col + 1) &&
                    !kingIsCheckInMove(board, row, col, BLACK, row, col + 2) &&
                    row == moveRow && col + 2 == moveCol)
                {
                    kingStatusBlack++;
                    towerBlackStatus++;
                    return true;
                }
            }
            else if (board[row][col - 1] == EMPTY && board[row][col - 2] == EMPTY &&
                     board[row][col - 4] == BLACK + TOWER)
            {
                if (!kingIsCheckInMove(board, row, col, BLACK, row, col - 1) &&
                    !kingIsCheckInMove(board, row, col, BLACK, row, col - 2) &&
                    row == moveRow && col - 2 == moveCol)
                {
                    kingStatusBlack++;
                    towerBlackStatus++;
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (!kingInCheck(board, color) && kingStatusBlack == 0 &&
            board[row][col] == KING && row == 0 && col == 4)
        {
            if (board[row][col + 1] == EMPTY && board[row][col + 2] == EMPTY &&
                board[row][col + 3] == TOWER)
            {
                if (!kingIsCheckInMove(board, row, col, WHITE, row, col + 1) &&
                    !kingIsCheckInMove(board, row, col, WHITE, row, col + 2) &&
                    row == moveRow && col + 2 == moveCol)
                {
                    kingStatusWhite++;
                    towerWhiteStatus++;
                    return true;
                }
            }
            else if (board[row][col - 1] == EMPTY && board[row][col - 2] == EMPTY &&
                     board[row][col - 4] == TOWER)
            {
                if (!kingIsCheckInMove(board, row, col, WHITE, row, col - 1) &&
                    !kingIsCheckInMove(board, row, col, WHITE, row, col - 2) &&
                    row == moveRow && col - 2 == moveCol)
                {
                    kingStatusWhite++;
                    towerWhiteStatus++;
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return false;
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
        // Checking diagonals (Bishop, Queen, King)
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
        if (kingInCheck(board, BLACK)) // In order to check for chess mate the king has to be threated
        {
            // We check the entire chessboard and se if we can stop the threat by any piece
            if (checkForAnyLegalMove(board, BLACK))
            {
                return false;
            }
            else
            {
                return true; // We didnt find any way to stop it. Checkmate is true
            }
        }
        else
        {
            return false;
        }
    }
    else if (color == WHITE)
    {
        if (kingInCheck(board, WHITE)) // In order to check for chess mate the king has to be threated
        {
            if (checkForAnyLegalMove(board, WHITE))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool checkForAnyLegalMove(char board[8][8], char color)
{
    bool valid;
    char piece;
    if (isBlack(color))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                piece = getPieceAtPosition(board, i, j);
                if (isBlack(piece))
                {
                    for (int y = 0; y < 8; y++)
                    {
                        for (int x = 0; x < 8; x++)
                        {
                            valid = validMoves(board, piece, i, j, y, x);
                            if (valid && !kingIsCheckInMove(board, i, j, BLACK, y, x))
                            {
                                return true; // if we finded a valid move which stops the threat there are no checkmate
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    else if (color == WHITE)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                piece = getPieceAtPosition(board, i, j);
                if (isWhite(piece))
                {
                    for (int y = 0; y < 8; y++)
                    {
                        for (int x = 0; x < 8; x++)
                        {
                            valid = validMoves(board, piece, i, j, y, x);
                            if (valid && !kingIsCheckInMove(board, i, j, WHITE, y, x))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}
bool gameEndsIndraw(char board[8][8])
{
    /*A chessgame will end in a draw if a player has no legal moves left but the king is not threated.
    Another case is when the game is in a situation where checkmate is impossible*/
    // No legal moves left
    struct coord a_piece, second;
    int pieces[2] = {HORSE, BISHOP};
    if (!checkForAnyLegalMove(board, BLACK) && !kingInCheck(board, BLACK))
    {
        return true;
    }
    else if (!checkForAnyLegalMove(board, WHITE) && !kingInCheck(board, WHITE))
    {
        return true;
    }
    else if (countPiecesOnBoard(board) == 2) // We only have the kings left. Impossible way for checkmate
    {
        return true;
    }
    else if (countPiecesOnBoard(board) == 3) // check if we have a Bishop or a Horse together with the kings
    {
        for (int i = 0; i < 2; i++)
        {
            a_piece = findPiece(board, BLACK, pieces[i]);
            second = findPiece(board, WHITE, pieces[i]);
            if (getPieceAtPosition(board, a_piece.row, a_piece.col) == pieces[i] + BLACK ||
                getPieceAtPosition(board, second.row, second.col) == pieces[i])
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}
struct coord findPiece(char board[8][8], char color, char piece)
{
    struct coord kingPos;
    if (isBlack(color))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPieceAtPosition(board, i, j) == piece + BLACK)
                {
                    kingPos.row = i;
                    kingPos.col = j;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPieceAtPosition(board, i, j) == piece)
                {
                    kingPos.row = i;
                    kingPos.col = j;
                }
            }
        }
    }
    return kingPos;
}