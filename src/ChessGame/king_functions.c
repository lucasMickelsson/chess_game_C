#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "king_functions.h"
#include "chessBoard.h"
#include "piece_functions.h"
#include "main.h"

bool kingIsCheckInMove(char board[8][8], int row, int col, int color, int moveRow, int moveCol)
{
    char tempBoard[8][8];
    copyBoard(board, tempBoard);
    changeBoard(tempBoard, row, col, moveRow, moveCol); // Make the planning move and check for threat
    if (kingInCheck(tempBoard, color))
    {
        if (getPieceAtPosition(board, row, col) == KING + color)
        {
            printf("The king will enter a square where it get threated, invalid!\n");
        }
        else
        {
            printf("The king is still in danger\n");
        }
        return true;
    }
    else
    {
        changeBoard(board, row, col, moveRow, moveCol);
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
                        moveThreatedKing(board, color, player);
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
    struct coord kingPos;
    if (isBlack(colorKing))
    {
        kingPos = findKing(board, BLACK);
        return !blackPieceIsSafe(board, kingPos.row, kingPos.col);
    }
    else
    {
        kingPos = findKing(board, WHITE);
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
    struct coord king;
    bool isValid = false;
    char newBoard[8][8];
    /*Checkmate will happen if king is threated and the player can not block it and not
    knock the piece out*/
    if (isBlack(color))
    {
        // First check if we can knock the piece or block the piece
        // Find the black king
        king = findKing(board, BLACK);
        if (!kingInCheck(board, BLACK)) // In order to check for chess mate the king has to be threated
        {
            copyBoard(board, newBoard); // We make a copy of the board
            // Check if we can move king to a place were its safe
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row + 1, king.col) &&
                king.row + 1 <= 7)
            {
                changeBoard(newBoard, king.row, king.col, king.row + 1, king.col);
                if (blackPieceIsSafe(newBoard, king.row + 1, king.col))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row + 1, king.col + 1) &&
                king.row + 1 <= 7 && king.col + 1 <= 7)
            {
                changeBoard(newBoard, king.row, king.col, king.row + 1, king.col + 1);
                if (blackPieceIsSafe(newBoard, king.row + 1, king.col + 1))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row, king.col + 1) &&
                king.col + 1 <= 7)
            {
                changeBoard(newBoard, king.row, king.col, king.row, king.col + 1);
                if (blackPieceIsSafe(newBoard, king.row, king.col + 1))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row - 1, king.col + 1) &&
                king.col + 1 <= 7 && king.row - 1 >= 0)
            {
                changeBoard(newBoard, king.row, king.col, king.row - 1, king.col + 1);
                if (blackPieceIsSafe(newBoard, king.row - 1, king.col + 1))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row - 1, king.col) &&
                king.row - 1 >= 0)
            {
                changeBoard(newBoard, king.row, king.col, king.row - 1, king.col);
                if (blackPieceIsSafe(newBoard, king.row - 1, king.col))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row - 1, king.col - 1) &&
                king.row - 1 >= 0 && king.col - 1 >= 0)
            {
                changeBoard(newBoard, king.row, king.col, king.row - 1, king.col - 1);
                if (blackPieceIsSafe(newBoard, king.row - 1, king.col - 1))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row, king.col - 1) &&
                king.col - 1 >= 0)
            {
                changeBoard(newBoard, king.row, king.col, king.row, king.col - 1);
                if (blackPieceIsSafe(newBoard, king.row, king.col - 1))
                {
                    return false;
                }
            }
            if (validMoves(newBoard, KING + BLACK, king.row, king.col, king.row + 1, king.col - 1) &&
                king.row + 1 <= 7 && king.col - 1 >= 0)
            {
                changeBoard(newBoard, king.row, king.col, king.row + 1, king.col - 1);
                if (blackPieceIsSafe(newBoard, king.row + 1, king.col - 1))
                {
                    return false;
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
    }
}
struct coord findKing(char board[8][8], char color)
{
    struct coord kingPos;
    if (isBlack(color))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPieceAtPosition(board, i, j) == KING + BLACK)
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
                if (getPieceAtPosition(board, i, j) == KING)
                {
                    kingPos.row = i;
                    kingPos.col = j;
                }
            }
        }
    }
    return kingPos;
}