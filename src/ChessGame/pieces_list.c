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

a_piece *push(a_piece *headptr, char data)
{
    a_piece *newpiece;
    newpiece = malloc(sizeof(a_piece));
    newpiece->the_piece = data;

    if (headptr == NULL)
    {
        headptr = newpiece;
        newpiece->next = NULL;
    }
    else
    {
        newpiece->next = headptr;
        headptr = newpiece;
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