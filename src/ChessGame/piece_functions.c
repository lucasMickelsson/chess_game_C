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
        isValidMove = checkTowerMoves(board, startRow, startCol, moveRow, moveCol);
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

    if (pawnWhiteStatus[col] == 0) // if the pawn is at the start position
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
bool checkTowerMoves(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = true;
    valid = horizontallyCheck(board, row, col, moveRow, moveCol);
    if (!valid)
    {
        valid = verticallyCheck(board, row, col, moveRow, moveCol);
    }
    return valid;
}
bool horizontallyCheck(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = true;
    char findPiece = getPieceAtPosition(board, row, col);
    if (isBlack(findPiece))
    {
        // Horizontally right check
        for (int i = col; (i + 1 <= 7 && board[row][i + 1] == EMPTY) ||
                          (checkForWhitePiece(board, row, i + 1) && row == moveRow && i + 1 == moveCol);
             i++)
        {
            DEBUG("Checking down vertiaclly");

            if (checkForWhitePiece(board, row, i + 1) && row == moveRow && i + 1 == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[row][i + 1] == EMPTY && row == moveRow && i + 1 == moveCol)
            {
                valid = true;
                return valid;
            }
            /*else
            {
                valid = false;
            }*/
        }
        // Horizontally left check
        for (int i = col; (i - 1 >= 0 && board[row][i - 1] == EMPTY) ||
                          (checkForWhitePiece(board, row, i - 1) && row == moveRow && i - 1 == moveCol);
             i--)
        {
            DEBUG("Checking down vertiaclly");
            if (checkForWhitePiece(board, row, i - 1) && row == moveRow && i - 1 == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[row][i - 1] == EMPTY && row == moveRow && i - 1 == moveCol)
            {
                DEBUG("to an empty position hor left");
                valid = true;
                return valid;
            }
            /*else
            {
                DEBUG("invalid hor left");
                valid = false;
            }*/
        }
    }
    else if (isWhite(findPiece))
    {
        // Horizontally left check
        for (int i = col; (i + 1 <= 7 && board[row][i + 1] == EMPTY) ||
                          (checkForBlackPiece(board, row, i + 1) && row == moveRow && i + 1 == moveCol);
             i++)
        {
            DEBUG("Checking down vertiaclly");

            if (checkForBlackPiece(board, row, i + 1) && row == moveRow && i + 1 == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[row][i + 1] == EMPTY && row == moveRow && i + 1 == moveCol)
            {
                valid = true;
                return valid;
            }
            /*else
            {
                valid = false;
            }*/
        }
        // Horizontally right check
        for (int i = col; (i - 1 >= 0 && board[row][i - 1] == EMPTY) ||
                          (checkForBlackPiece(board, row, i - 1) && row == moveRow && i - 1 == moveCol);
             i--)
        {
            DEBUG("Checking down vertiaclly");
            if (checkForBlackPiece(board, row, i - 1) && row == moveRow && i - 1 == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[row][i - 1] == EMPTY && row == moveRow && i - 1 == moveCol)
            {
                DEBUG("to an empty position hor left");
                valid = true;
                return valid;
            }
            /*else
            {
                DEBUG("invalid hor left");
                valid = false;
            }*/
        }
    }
    valid = false;
    return valid;
}
bool verticallyCheck(char board[8][8], int row, int col, int moveRow, int moveCol)
{
    bool valid = true;
    char findPiece = getPieceAtPosition(board, row, col);
    if (isBlack(findPiece))
    {
        // Vertical down check
        for (int i = row; (i - 1 >= 0 && board[i - 1][col] == EMPTY) ||
                          (checkForWhitePiece(board, i - 1, col) && i - 1 == moveRow && col == moveCol);
             i--)
        {
            DEBUG("Checking down vertiaclly");
            if (checkForWhitePiece(board, i - 1, col) && i - 1 == moveRow && col == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[i - 1][col] == EMPTY && i - 1 == moveRow && col == moveCol)
            {
                DEBUG("to an empty position down check");

                valid = true;
                return valid;
            }
            /*else
            {
                DEBUG("Not valid down check");
                valid = false;
            }*/
        }
        // Vertical up check
        for (int i = row; (i + 1 <= 7 && board[i + 1][col] == EMPTY) ||
                          (checkForWhitePiece(board, i + 1, col) && i + 1 == moveRow && col == moveCol);
             i++)
        {
            DEBUG("Checking down vertiaclly");
            if (checkForWhitePiece(board, i + 1, col) && i + 1 == moveRow && col == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[i + 1][col] == EMPTY && i + 1 == moveRow && col == moveCol)
            {
                DEBUG("to an empty position vert up");
                valid = true;
                return valid;
            }
            /*else
            {
                DEBUG("inavlid vert up");
                valid = false;
            }*/
        }
    }
    else if (isWhite(findPiece))
    {
        // Vertical down check
        for (int i = row; (i - 1 >= 0 && board[i - 1][col] == EMPTY) ||
                          (checkForBlackPiece(board, i - 1, col) && i - 1 == moveRow && col == moveCol);
             i--)
        {
            DEBUG("Checking down vertiaclly");
            if (checkForBlackPiece(board, i - 1, col) && i - 1 == moveRow && col == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[i - 1][col] == EMPTY && i - 1 == moveRow && col == moveCol)
            {
                DEBUG("to an empty position down check");

                valid = true;
                return valid;
            }
            /*else
            {
                DEBUG("Not valid down check");
                valid = false;
            }*/
        }
        // Vertical up check
        for (int i = row; (i + 1 <= 7 && board[i + 1][col] == EMPTY) ||
                          (checkForBlackPiece(board, i + 1, col) && i + 1 == moveRow && col == moveCol);
             i++)
        {
            DEBUG("Checking down vertiaclly");
            if (checkForBlackPiece(board, i + 1, col) && i + 1 == moveRow && col == moveCol)
            {
                DEBUG("down a white piece");
                valid = true;
                return valid;
            }
            else if (board[i + 1][col] == EMPTY && i + 1 == moveRow && col == moveCol)
            {
                DEBUG("to an empty position vert up");
                valid = true;
                return valid;
            }
            /*else
            {
                DEBUG("inavlid vert up");
                valid = false;
            }*/
        }
    }
    valid = false;
    return valid;
}