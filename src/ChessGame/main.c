#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
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

void printStart(void)
{
    int confirm;
    do
    {
        system("cls"); // clear the screen from previous output of meny
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
            selectNumbOfPlayers();
            break;

        case 2:
            selectNumbOfPlayers();
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
void selectNumbOfPlayers()
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
            // function for starting the game
            break;

        case 2:
            print1PlayerModeInfo();
            // function for starting the game
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
    printf("\n\nWelcome to 1-player chess! enter input as shown: squareToStart\n");
    printf("Then enter the endsquare for choosen piece: squareToEnd\n");
    printf("you will play as white while the AI plays as black.\n");
    printf("enter 'exit' to leave the mode\n\n");
}
void print2PlayerModeInfo()
{
    printf("\n\nWelcome to 2-player chess! enter input as shown: squareToStart\n");
    printf("Then enter the endsquare for choosen piece: squareToEnd\n");
    printf("for example, to move the piece at A1 to B2, you would type: A1 then enter\n");
    printf("Then you type in: B2 then enter\n");
    printf("One of you plays as white an the other one as black\n");
    printf("enter 'exit' to leave the mode\n\n");
}

void player1()
{
}

void player2()
{
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