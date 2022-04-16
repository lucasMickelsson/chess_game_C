#include <stdio.h>
#include "chessBoard.h"
#define TEST_CASE(name) printf("\nRUNNING CASE: %s\n", name)
#define VERIFY(cond, msg)             \
    if (cond)                         \
        printf("SUCCESS: %s\n", msg); \
    else                              \
        printf("FAIL: %s\n", msg);

int main(void)
{
    TEST_CASE("Init a new chessBoard");
    char board[8][8];
    initChessBoard(board);

    TEST_CASE("Get a specific piece at given position");
    char getPiece = getPieceAtPosition(board, 0, 0);
    VERIFY(getPiece == TOWER, "Its a white tower");
    getPiece = getPieceAtPosition(board, 1, 0);
    VERIFY(getPiece == PAWN, "Its a white pawn");

    getPiece = getPieceAtPosition(board, 6, 0);
    VERIFY(getPiece == PAWN + BLACK, "Its a black pawn");

    getPiece = getPieceAtPosition(board, 0, 9);
    VERIFY(getPiece == -1, "Its an illegal position");

    getPiece = getPieceAtPosition(board, -1, 6);
    VERIFY(getPiece == -1, "Its an illegal position");

    TEST_CASE("Print the board");
    printf("\n\n");
    printBoard(board);

    TEST_CASE("Ge coords for a chessboard via chess move");
    struct chessCoord test;
    char *string1 = "A8";
    test = getChessCoordsIn(string1);
    printf("Chess coords are %d %c\n", test.row, test.col);

    string1 = "B3";
    test = getChessCoordsIn(string1);
    printf("Chess coords are %d %c", test.row, test.col);
}