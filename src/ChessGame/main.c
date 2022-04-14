#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "chessBoard.h"
#include "main.h"

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
            selectNumbOfPlayers(option);
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

void modeOptions()
{
    printf("\nSelect number of players:\n\n");
    printf("1. 2 players\n");
    printf("\n2. 1 player (You vs AI)\n");
    printf("\n3. Return back\n\n");
}
void selectNumbOfPlayers(int choice)
{
    bool back = false;
    int option;
    do
    {
        printLogo();
        modeOptions();
        option = user_selection();
        switch (option)
        {
        case 1:
            print2PlayerModeInfo();
            chessGameGo(choice);
            break;

        case 2:
            print1PlayerModeInfo();
            // chessGameGo(choice);
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
void print1PlayerModeInfo()
{
    clearScreen();
    printf("\n\nWelcome to 2-player chess! enter input as shown: pieceId piecePosition\n");
    printf("Id for white pieces: Pawn=1 Tower=2 Horse=3 Bishop=4 Queen=5 King=6\n");
    printf("Then you enter endposition for the piece, for example to move a King, you would enter: B2\n");
    printf("One of you plays as white an the other one as black\n");
    printf("enter 'exit' to leave the mode while playing\n\n");
    printf("you will play as white while the AI plays as black.\n");
    printf("enter 'exit' to leave the mode while playing\n\n");
    confirm();
    clear_buffer();
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
    printf("\n\nWelcome to 2-player chess! enter input as shown: pieceId piecePosition\n");
    printf("Id for white pieces: Pawn=1 Tower=2 Horse=3 Bishop=4 Queen=5 King=6\n");
    printf("Id for black pieces: Pawn=51 Tower=52 Horse=53 Bishop=54 Queen=55 King=56\n");
    printf("Then you enter endposition for the piece, for example to move a King, you would enter: B2\n");
    printf("Player 1 plays as white while player 2 plays as black\n");
    printf("enter 'exit' to leave the mode while playing\n\n");
    confirm();
    clear_buffer();
}

int player1(char board[8][8])
{
    char command[10];
    bool validMove = false;
    char *piece, *start;
    printf("\nPlayer 1 Turn:\n");

    printf("Enter the white piece to move: ");
    // here we have to add functions for checking input
    do
    {
        readString(command, 10);
        if (equalStrings(command, "quit"))
        {
            break;
        }

        piece = strtok(command, " ");
        start = strtok(NULL, " ");

        if (piece == NULL || start == NULL)
        {
            printf("Invalid input for chess move try again: ");
        }
        else
        {
            validMove = true;
        }
    } while (!validMove);

    if (equalStrings(command, "quit"))
    {
        return -1;
    }
    else
    {
        return true;
    }
}

int player2(char board[8][8])
{
    char command[10];
    char *piece, *start;
    bool validMove = false;
    printf("\nPlayer 2 Turn:\n");

    printf("Enter the black piece to move: ");

    // here we have to add functions for checking input

    do
    {
        readString(command, 10);
        if (equalStrings(command, "quit"))
        {
            break;
        }

        piece = strtok(command, " ");
        start = strtok(NULL, " ");

        if (piece == NULL || start == NULL)
        {
            printf("Invalid input for chess move try again: ");
        }
        else
        {
            validMove = true;
        }
    } while (!validMove);

    if (equalStrings(command, "quit"))
    {
        return -1;
    }
    else
    {
        return true;
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
        printBoard(chessBoard);
        temp = player2(chessBoard);
        if (temp == -1)
        {
            printf("Player 2 choosed to end the game\n\n");
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