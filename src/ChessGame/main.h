#ifndef MAINH
#define MAINH

void printLines(void);
void clear_buffer();
int user_selection();
void printChessModeOptions();
void handleChessOptions();
bool playComputerOrNot();
void printLogo(void);
void printWelcomeMessage(void);
void printStart(void);
void printMenyOptions();
void clear_buffer();
void selectNumbOfPlayers(int choice);
void modeOptions(void);
void print1PlayerModeInfo();
void print2PlayerModeInfo();
void confirm();
void chessGameGo(int chessMode);
void readString(char array[], int size);
char *player1(char board[8][8]);
char *player2(char board[8][8]);
bool equalStrings(char *string1, char *string2);
void clearScreen(void);

#endif
