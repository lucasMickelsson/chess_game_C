#ifndef PIECESH
#define PIECESH
#include <stdbool.h>

/*We will store total number of pieces in a list */
typedef struct piece_list
{
    char the_piece;
    struct piece_list *next;
} a_piece;

/**
 * Function for insert a piece into the list
 * @param headptr pointer to the head of list
 * @return the new header
 */
a_piece *push(a_piece *headptr, char data);

/**
 * Function for creating a new list
 * @return a new list which is Null
 */
a_piece *create_list();

/**
 * Function for checking if list is empty or not
 * @param headptr header of the list
 * @return true if list is empty false otherwise
 */
bool list_empty(a_piece *headptr);

/**
 * Function for delete a whole list
 * @param headptr the header
 * @return NULL after deletion
 */
a_piece *delete_list(a_piece *headptr);

void printList(a_piece *head);

#endif