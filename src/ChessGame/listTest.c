#include <stdio.h>
#include "pieces_list.h"
#include "chessBoard.h"
#define TEST_CASE(name) printf("\nRUNNING CASE: %s\n", name)
#define VERIFY(cond, msg)             \
    if (cond)                         \
        printf("SUCCESS: %s\n", msg); \
    else                              \
        printf("FAIL: %s\n", msg);

int main(void)
{
    TEST_CASE("Create new list");
    a_piece *thelist;
    thelist = create_list();
    VERIFY(list_empty(thelist), "list is empty");

    TEST_CASE("Insert a node into the list");
    piece newOne;
    newOne.color = WHITE;
    newOne.piece_dead = false;
    newOne.pieceID = KING;

    thelist = push(thelist, newOne);

    VERIFY(!list_empty(thelist), "list is not empty");

    piece onemore;
    onemore.color = BLACK;
    onemore.piece_dead = true;
    onemore.pieceID = QUEEN;
    thelist = push(thelist, onemore);

    TEST_CASE("Delete the list");
    thelist = delete_list(thelist);
    VERIFY(list_empty(thelist), "list is empty and got successfully deleted");
}