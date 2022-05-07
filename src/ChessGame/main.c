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

int kingStatusBlack = 0, kingStatusWhite = 0, tower1WhiteStatus = 0, tower1BlackStatus = 0,
    tower2BlackStatus = 0, tower2WhiteStatus = 0;

a_piece *the_list = NULL;

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
            printPawnChessInfo();
            chessGameGo(option);
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
    printf("\nPress any key to continue");
    getch();
    printf("\n\n\n");
}
void print2PlayerModeInfo()
{
    clearScreen();
    printf("\n\nWelcome to classic chess! enter input as shown: pieceStartPosition pieceEndPosition\n");
    printf("For example to move a piece from A2 to B2 enter input: A2 B2\n");
    printf("Player 1 plays as white while player 2 plays as black\n");
    printf("enter 'quit' to leave the mode\n");
    confirm();
    clear_buffer();
}
void printPawnChessInfo()
{
    clearScreen();
    printf("\n\nWelcome to pawn chess! enter input as shown: pieceStartPosition pieceEndPosition\n");
    printf("For example to move a piece from A2 to B2 enter input: A2 B2\n");
    printf("Your mission to win the game is to make it to the final row using a random pawn\n");
    printf("When a pawn have reached to the final row it will promote to a randomly choosen piece from the player\n");
    printf("(Queen, Bishop, Tower, Horse)\n");
    printf("Player 1 plays as white while player 2 plays as black\n");
    printf("enter 'quit' to leave the mode\n");
    confirm();
    clear_buffer();
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
                        printf("The king is still in danger after that move\n");
                        moveThreatedKing(board, color, player);
                    }
                    else
                    {
                        the_list = changeBoard(board, p1.row, p1.col, p2.row, p2.col, the_list);
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
                        printf("The king is still in danger after that move\n");
                        moveThreatedKing(board, color, player);
                    }
                    else
                    {
                        the_list = changeBoard(board, p1.row, p1.col, p2.row, p2.col, the_list);
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

    do
    {
        readString(command, 10);
        if (strcmp(command, "quit") == 0)
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
                    if ((checkValidRockedMove(board, p1.row, p1.col, WHITE, p2.row, p2.col) &&
                         kingStatusWhite == 0) ||
                        (checkValidRockedMove(board, p1.row, p1.col, WHITE, p2.row, p2.col) &&
                         kingStatusWhite == 0))
                    {
                        DEBUG("We finded valid rocked move tower");
                        if (p2.row == 0 && p2.col == 2 && tower1WhiteStatus == 0)
                        {
                            DEBUG("We make a rocked move using left tower");
                            the_list = makeRockMove(board, WHITE, p1.row, p1.col, p2.row, p2.col, the_list);
                            kingStatusWhite++;
                            break;
                        }
                        else if (p2.row == 0 && p2.col == 6 && tower2WhiteStatus == 0)
                        {
                            DEBUG("We make a rocked move using right tower");
                            the_list = makeRockMove(board, WHITE, p1.row, p1.col, p2.row, p2.col, the_list);
                            kingStatusWhite++;
                            break;
                        }
                    }
                    validMove = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                    if (!validMove)
                    {
                        DEBUG("invalid move");
                        printf("The chess move is invalid, try again: ");
                    }
                    else
                    {
                        the_list = changeBoard(board, p1.row, p1.col, p2.row, p2.col, the_list);
                        if (kingInCheck(board, WHITE))
                        {
                            printf("The white king will enter a square where it get threated, invalid!\n");
                            setPieceAtPosition(board, KING, p1.row, p1.col);
                            setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                            player1(board);
                        }
                        kingStatusWhite++;
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
                        if (kingIsCheckInMove(board, p1.row, p1.col, WHITE, p2.row, p2.col))
                        {
                            printf("The white king will be in danger after that move!\n");
                            player1(board);
                        }
                        else
                        {
                            the_list = changeBoard(board, p1.row, p1.col, p2.row, p2.col, the_list);
                        }
                        if (pieceStart == TOWER && p1.col == 0)
                        {
                            tower1WhiteStatus++;
                        }
                        else if (pieceStart == TOWER && p1.col == 7)
                        {
                            tower2WhiteStatus++;
                        }
                        else if (getPieceAtPosition(board, p2.row, p2.col) == PAWN &&
                                 p2.row == 7)
                        {
                            pawnLastPosStatusSet(board, p2.row, p2.col);
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
    int result;
    struct coord p1, p2;

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
            printf("Invalid input for chess move try again in this format(startPos endPos): ");
        }
        else if (positionStrings(start) && positionStrings(end))
        {
            p1 = getChessIndex(start);
            p2 = getChessIndex(end);
            char pieceStart = getPieceAtPosition(board, p1.row, p1.col);
            validMove = isBlack(pieceStart);
            if (!validMove)
            {
                printf("Not a valid piece for player 2, should use white pieces: ");
            }
            else
            {
                if (pieceStart == KING + BLACK)
                {
                    char Oldpiece = getPieceAtPosition(board, p2.row, p2.col);
                    if ((checkValidRockedMove(board, p1.row, p1.col, BLACK, p2.row, p2.col) &&
                         kingStatusBlack == 0) ||
                        (checkValidRockedMove(board, p1.row, p1.col, BLACK, p2.row, p2.col) &&
                         kingStatusBlack == 0))
                    {
                        DEBUG("We finded valid rocked move tower");
                        if (p2.row == 7 && p2.col == 2 && tower1BlackStatus == 0)
                        {
                            DEBUG("We make a rocked move using left tower");
                            the_list = makeRockMove(board, BLACK, p1.row, p1.col, p2.row, p2.col, the_list);
                            kingStatusBlack++;
                            break;
                        }
                        else if (p2.row == 0 && p2.col == 6 && tower2BlackStatus == 0)
                        {
                            DEBUG("We make a rocked move using right tower");
                            the_list = makeRockMove(board, BLACK, p1.row, p1.col, p2.row, p2.col, the_list);
                            kingStatusBlack++;
                            break;
                        }
                    }
                    validMove = validMoves(board, pieceStart, p1.row, p1.col, p2.row, p2.col);
                    if (!validMove)
                    {
                        printf("The chess move is invalid, try again: ");
                    }
                    else
                    {
                        the_list = changeBoard(board, p1.row, p1.col, p2.row, p2.col, the_list);
                        if (kingInCheck(board, BLACK))
                        {
                            printf("The black king will enter a square where it get threated, invalid!\n");
                            setPieceAtPosition(board, KING + BLACK, p1.row, p1.col);
                            setPieceAtPosition(board, Oldpiece, p2.row, p2.col);
                            player2(board);
                        }
                        kingStatusBlack++;
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
                        if (kingIsCheckInMove(board, p1.row, p1.col, BLACK, p2.row, p2.col))
                        {
                            printf("The black king will be in danger after that move!\n");
                            player2(board);
                        }
                        else
                        {
                            the_list = changeBoard(board, p1.row, p1.col, p2.row, p2.col, the_list);
                        }
                        if (pieceStart == TOWER + BLACK && p1.col == 0)
                        {
                            tower1BlackStatus++;
                        }
                        else if (pieceStart == TOWER + BLACK && p1.col == 7)
                        {
                            tower2BlackStatus++;
                        }
                        else if (getPieceAtPosition(board, p2.row, p2.col) == PAWN + BLACK &&
                                 p2.row == 0)
                        {
                            pawnLastPosStatusSet(board, p2.row, p2.col);
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
void pawnLastPosStatusSet(char board[8][8], int row, int col)
{
    int choice;
    printf("The pawn has enter the last position of the chessboard\n");
    printf("The pawn will now change to any one of the following pieces:\n");
    printf("Tower=2, Horse=3, Bishop=4, Queen=5\n");
    do
    {
        choice = user_selection();
        clear_buffer();
    } while (choice < 2 || choice > 5);

    if (isBlack(getPieceAtPosition(board, row, col)))
    {
        setPieceAtPosition(board, choice + BLACK, row, col);
    }
    else
    {
        setPieceAtPosition(board, choice, row, col);
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
    bool go = true;
    int temp;
    char chessBoard[8][8];
    if (chessMode == 1)
    {
        initChessBoard(chessBoard);
    }
    else if (chessMode == 2)
    {
        initPawnChessboard(chessBoard);
    }
    while (go)
    {
        printBoard(chessBoard, the_list);
        temp = player1(chessBoard);
        if (temp == -1)
        {
            printf("Player 1 want to quit the game!\n");
            printf("Player 2 would you accept it? Enter y for yes?\n");
            if (confirmQuitGame())
            {
                break;
            }
            else
            {
                continue;
            }
        }
        else if (checkMate(chessBoard, BLACK))
        {
            printBoard(chessBoard, the_list);
            printf("\nThe game is over and player 1 White wins!\n\n");
            confirm();
            break;
        }
        else if (!checkForAnyLegalMove(chessBoard, BLACK))
        {
            printBoard(chessBoard, the_list);
            if (gameEndsIndraw(chessBoard))
            {
                printf("\nThe game ended in a draw no winner!\n");
                confirm();
                break;
            }
        }
        printBoard(chessBoard, the_list);
        temp = player2(chessBoard);
        if (temp == -1)
        {
            printf("Player 2 want to quit the game!\n");
            printf("Player 1 would you accept it? Enter y for yes?\n");
            if (confirmQuitGame())
            {
                break;
            }
            else
            {
                continue;
            }
        }
        else if (checkMate(chessBoard, WHITE))
        {
            printBoard(chessBoard, the_list);
            printf("\nThe game is over and player 2 Black wins!\n\n");
            confirm();
            break;
        }
        else if (!checkForAnyLegalMove(chessBoard, WHITE))
        {
            printBoard(chessBoard, the_list);
            if (gameEndsIndraw(chessBoard))
            {
                printf("\nThe game ended in a draw no winner!\n");
                confirm();
                break;
            }
        }
    }
    tower1WhiteStatus = 0, tower2WhiteStatus = 0, kingStatusWhite = 0, kingStatusBlack = 0,
    tower1BlackStatus = 0, tower2BlackStatus = 0;
    the_list = delete_list(the_list);
}
bool confirmQuitGame()
{
    char choice;
    scanf(" %c", &choice);
    clear_buffer();
    if (choice == 'y')
    {
        return true;
    }
    else
    {
        return false;
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
            readAndWrite();
            confirm();
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
void readAndWrite()
{
    FILE *fileptr;
    char ch;
    fileptr = fopen("chess.txt", "r");

    if (fileptr == NULL)
    {
        printf("Could not open file for reading!\n");
    }
    else
    {
        do
        {
            ch = fgetc(fileptr);
            printf("%c", ch);
        } while (ch != EOF);
    }
    fclose(fileptr);
}