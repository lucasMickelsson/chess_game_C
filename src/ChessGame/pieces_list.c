#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pieces_list.h"

a_piece *create_list()
{
    return NULL;
}
bool list_empty(a_piece *headptr)
{
    if (headptr == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

a_piece *push(a_piece *headptr, piece data)
{
    a_piece *newpiece;
    newpiece = malloc(sizeof(a_piece));
    newpiece->the_piece = data;

    if (list_empty(headptr))
    {
        newpiece->next = NULL;
        newpiece = headptr;
    }
    else
    {
        newpiece->next = headptr;
        newpiece = headptr;
    }
    return headptr;
}
a_piece *delete_list(a_piece *headptr)
{
    a_piece *current = headptr;
    a_piece *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    headptr = NULL;

    return headptr;
}