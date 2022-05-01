#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "chessBoard.h"
#include "main.h"
#include "piece_functions.h"
#include "debug.h"
#include "pieces_list.h"
#include "king_functions.h"
#define play1 1
#define play2 2

void printLines(void)
{
    printf("\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            printf("-");
        }
        printf("\n");
    }
}
void printLogo(void)
{
    printLines();
    printf("    _____ _    _ ______  _____ _____\n");
    printf("   / ____| |  | |  ____|/ ____/ ____|\n");
    printf("  | |    | |__| | |__  | (___| (___ \n");
    printf("  | |    |  __  |  __|  \\___ \\\\___ \\ \n");
    printf("  | |____| |  | | |____ ____) |___) |\n");
    printf("   \\_____|_|  |_|______|_____/_____/\n\n");
    printLines();
}
void printWelcomeMessage(void)
{
    printf("    Welcome to chess game by Lucas Mickelsson\n");
    printf("           'press enter to continue'");
}
void clearScreen(void)
{
    system("cls");
}

void printStart(void)
{
    int confirm;
    do
    {
        clearScreen(); // clear the screen from previous output of meny
        printLogo();
        printWelcomeMessage();
        confirm = getch();
    } while (confirm != 13);
}
void printMenyOptions()
{
    printf("\nChess Menu options:\n\n");
    printf("1. Play Chess\n");
    printf("\n2. Chess Rules\n");
    printf("\n3. Quit\n\n");
}
void clear_buffer()
{
    while (getchar() != '\n')
    {
    }
}
int user_selection()
{
    int selection;
    printf("Your choice: ");
    while (scanf("%d", &selection) != 1)
    {
        printf("Invalid input\n");
        clear_buffer();
        printf("Try again: ");
    }
    return selection;
}

void printChessModeOptions()
{
    printf("\nChess options:\n\n");
    printf("1. Play Classic Chess\n");
    printf("\n2. Play Pawn Chess\n");
    printf("\n3. Return back to main menu\n\n");
}
void handleChessOptions()
{
    bool back = false;
    int option;
    do
    {
        printLogo();
        printChessModeOptions();
        option = user_selection();
        switch (option)
        {
        case 1:
            print2PlayerModeInfo();
            chessGameGo(option);
            break;

        case 2:
            // selectNumbOfPlayers(option);
            break;

        case 3:
            back = true;
            break;

        default:
            printf("Invalid option");
            break;
        }
    } while (!back);
}
void confirm()
{
    printf("Press any key to continue");
    getch();
    printf("\n\n\n");
}
void print2PlayerModeInfo()
{
    clearScreen();
    printf("\n\nWelcome to 2-player chess! enter input as shown: pieceStartPosition pieceEndPosition\n");
    printf("For example to move a piece from A2 to B2 enter input: A2 B2\n");
    printf("Player 1 plays as white while player 2 plays as black\n");
    printf("enter 'quit' to leave the mode while playing\n\n");
    confirm();
    clear_buffer();
}

int player1(char board[8][8])
{
    char command[10];
    bool validMove = false;
    char *end, *start;
    int result;
    struct coord p1, p2;

    if (kingInCheck(board, WHITE))
    {
        // Function for moving a therated king
        result = moveThreatedKing(board, WHITE, play1);
        if (result == -1)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    printf("\nPlayer 1 Turn:\n");

    printf("Enter chess move to make(startPos endPos): ");
    // here we have to add functions for checking input
    do
    {
        readString(command, 10);
        if (equalStrings(command, "quit"))
        {
            break;
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
            // printf("Coors are %d %d\n", p1.row, p1.col);
            char pieceStart = getPieceAtPosition(board, p1.row, p1.col);
            validMove = isWhite(pieceStart);
            if (!validMove)
            {
                printf("Not a valid piece for player 1, should use white pieces: ");
            }
            else
            {
                if (pieceStart == KING)
                {
                    char Oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                    validMove = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                    if (!validMove)
                    {
                        printf("The chess move is invalid, try again: ");
                    }
                    else
                    {
                        changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                        if (kingInCheck(board, WHITE))
                        {
                            printf("The white king will enter a square where it get threated, invalid!\n");
                            setPieceAtPosition(board, KING, p1.row, p1.col);
                            setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                            player1(board);
                        }
                    }
                }
                else
                {
                    validMove = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                    if (!validMove)
                    {
                        printf("The chess move is invalid, try again: ");
                    }
                    else
                    {
                        char Oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                        changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                        if (kingInCheck(board, WHITE))
                        {
                            printf("The white king will enter a square where it get threated, invalid!\n");
                            setPieceAtPosition(board, pieceStart, p1.row, p1.col);
                            setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                            player1(board);
                        }
                    }
                }
            }
        }
        else
        {
            printf("Not a valid chess command try again: ");
        }
    } while (!validMove);

    if (equalStrings(command, "quit"))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int player2(char board[8][8])
{
    char command[10];
    bool validMove = false;
    char *end, *start;
    struct coord p1, p2;
    int result;

    if (kingInCheck(board, BLACK))
    {
        // Function for moving a therated king
        result = moveThreatedKing(board, BLACK, play2);
        if (result == -1)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    printf("\nPlayer 2 Turn:\n");

    printf("Enter chess move to make(startPos endPos): ");
    do
    {
        readString(command, 10);
        if (equalStrings(command, "quit"))
        {
            break;
        }

        start = strtok(command, " ");
        end = strtok(NULL, " ");

        if (start == NULL || end == NULL)
        {
            printf("Invalid input for chess move try again: ");
        }
        else if (positionStrings(start) && positionStrings(end))
        {

            p1 = getChessIndex(start);
            p2 = getChessIndex(end);
            char pieceStart = getPieceAtPosition(board, p1.row, p1.col);
            validMove = isBlack(pieceStart);
            if (!validMove)
            {
                printf("Not a valid piece for player 2, should use black pieces: ");
            }
            else
            {
                if (pieceStart == KING + BLACK)
                {
                    char Oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                    validMove = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                    if (!validMove)
                    {
                        printf("The chess move is invalid, try again: ");
                    }
                    else
                    {
                        changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                        if (kingInCheck(board, BLACK))
                        {
                            printf("The king will enter a square where it get threated, invalid!\n");
                            setPieceAtPosition(board, KING + BLACK, p1.row, p1.col);
                            setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                            player2(board);
                        }
                    }
                }
                else
                {
                    char Oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                    validMove = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                    if (!validMove)
                    {
                        printf("The chess move is invalid, try again: ");
                    }
                    else
                    {
                        changeBoard(board, p1.row, p1.col, p2.row, p2.col);
                        if (kingInCheck(board, BLACK))
                        {
                            printf("The king will be threated after that move!\n");
                            setPieceAtPosition(board, pieceStart, p1.row, p1.col);
                            setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                            player2(board);
                        }
                    }
                }
            }
        }
        else
        {
            printf("Not a valid chess command try again: ");
        }
    } while (!validMove);

    if (equalStrings(command, "quit"))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
bool equalStrings(char *string1, char *string2)
{
    if (strcmp(string1, string2) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void chessGameGo(int chessMode)
{
    // a_piece *newList = create_list();
    char chessBoard[8][8];
    initChessBoard(chessBoard);
    bool go = true;
    int temp;
    while (go)
    {
        printBoard(chessBoard);
        temp = player1(chessBoard);
        if (temp == -1)
        {
            printf("Player 1 choosed to end the game\n\n");
            break;
        }
        else if (checkMate(chessBoard, BLACK))
        {
            printBoard(chessBoard);
            printf("\nThe game is over and player 1 White wins!\n\n");
            confirm();
            break;
        }
        printBoard(chessBoard);
        temp = player2(chessBoard);
        if (temp == -1)
        {
            printf("Player 2 choosed to end the game\n\n");
            break;
        }
        else if (checkMate(chessBoard, WHITE))
        {
            printBoard(chessBoard);
            printf("\nThe game is over and player 2 Black wins!\n\n");
            confirm();
            break;
        }
    }
}

void readString(char array[], int size)
{
    fgets(array, size, stdin);
    int length = strlen(array);

    if (array[length - 1] == '\n')
    {
        array[length - 1] = '\0';
    }
    else
    {
        clear_buffer();
    }
}

int main(void)
{
    bool exitProgram = false;
    int choice;
    printStart();

    do
    {
        printLogo();
        printMenyOptions();
        choice = user_selection();

        switch (choice)
        {
        case 1:
            handleChessOptions();
            break;

        case 2:
            printf("This is the rules");
            break;

        case 3:
            exitProgram = true;
            break;

        default:
            printf("Invalid option");
            break;
        }

    } while (!exitProgram);

    return 0;
}