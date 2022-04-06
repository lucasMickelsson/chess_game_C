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

#endif