#ifndef PIECESH
#define PIECESH

// every chess piece has been given an unique id
// black pieces will have pieceID + 50
#define BLACK 50
#define WHITE 0
#define EMPTY 0

#define PAWN 1
#define TOWER 2
#define HORSE 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

typedef struct piece
{
    char color;
    char pieceID;
    char posX;
    char poxY;
    bool piece_dead;
} piece;

typedef struct piece_list
{
    piece the_piece;
    struct piece_list *next;
} a_piece;

#endif