#ifndef MAINH
#define MAINH
#include <stdbool.h>
#include "pieces_list.h"

/**
 * Function for printing lines for chess logo
 */
void printLines(void);
/**
 * Function for clearing the input buffer
 */
void clear_buffer();

/**
 * Function for user input. We use it for meny selections
 * @return the option user choosed
 */
int user_selection();
/**
 * Function for printing main menu options
 */
void printChessModeOptions();

/**
 * Function for handle chess mode options, here the user can select chess option
 */
void handleChessOptions();

/**
 * Function for printing the chess logo when the game starts
 */
void printLogo(void);

/**
 * Function for printing the welcome message to the game
 */
void printWelcomeMessage(void);

/**
 * Function ofr printing the first message and press any key
 */
void printStart(void);

/**
 * Function for printing main menu option
 */
void printMenyOptions();

/**
 * Function for printing out info about classic chess and how to make a move
 */
void print2PlayerModeInfo();

/**
 * Function for printing out info about pawn chess and how to make a move
 */
void printPawnChessInfo();

/**
 * This function let the user press any key to go forward at menu
 */
void confirm();

/**
 * Function for executing the game
 * @param chessMode the chess mode the user want to play
 */
void chessGameGo(int chessMode);

/**
 * Function for reading a string in this case a chess move
 * @param array the string array
 * @param size the size of the array
 */
void readString(char array[], int size);

/**
 * Function for player 1 white making a chess move
 * @param board the chessboard for now
 * @return if the move was valid at the end 1 will be returned. If 'quit' was written the game will end
 */
int player1(char board[8][8]);

/**
 * Function for player 2 black making a chess move
 * @param board the chessboard for now
 * @return if the move was valid at the end 1 will be returned. If 'quit' was written the game will end
 */
int player2(char board[8][8]);

/**
 * Function for clearing the whole sreen
 */
void clearScreen(void);

/**
 * Function for handleing situation when a pawn have reached to the fina row
 * @param board the chessboard
 * @param row the pawn position row
 * @param col the pawn position col
 */
void pawnLastPosStatusSet(char board[8][8], int row, int col);

/**
 * Function for let a player accept other player leaving the game
 * @return true if the user did accept it false otherwise
 */
bool confirmQuitGame();

/**
 * Function for reading and printing out the instructions for a chess game
 */
void readAndWrite();

/**
 *Function for removing blanks at the beginnning of a string
 * @param string the string to be trimmed
 */
void trimLeft(char string[]);

/**
 * Function for making a string a chess move
 * @param string the string to be normalized
 */
void normalize(char string[]);

#endif