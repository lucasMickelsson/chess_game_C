#ifndef PIECESH
#define PIECESH

int pawnBlackStatus[8] = {0};
int pawnWhiteStatus[8] = {0};

typedef struct piece
{
    char color;
    char pieceID;
    bool piece_dead;
} piece;

/*We will store total number of pieces in a list */
typedef struct piece_list
{
    piece the_piece;
    struct piece_list *next;
} a_piece;

#endif