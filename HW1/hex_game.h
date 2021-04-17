#ifndef hex_game
#define hex_game

/* Library of hex_game */


#define FIXED_SIZE 12

/* Function declarations */

bool checkWin(char board[FIXED_SIZE][FIXED_SIZE],int current_row,int current_column,int board_size,int visited[FIXED_SIZE][FIXED_SIZE],char sign);
int charToInt(char column);
bool checkMove(char board[FIXED_SIZE][FIXED_SIZE],int column,int row);
bool checkInput(int column, int row,int board_size);
void printBoard(char board[FIXED_SIZE][FIXED_SIZE], int board_size);
void botTurn(char board[FIXED_SIZE][FIXED_SIZE], int board_size);
bool playerTurn(char sign,char board[FIXED_SIZE][FIXED_SIZE], int board_size);
bool isBoardFull(char board[FIXED_SIZE][FIXED_SIZE],int board_size);
void playerVsPlayer(char board[FIXED_SIZE][FIXED_SIZE], int board_size);
void initializeVisitedArray(int board_size,int visited[FIXED_SIZE][FIXED_SIZE]);
void playerVsBot(char board[FIXED_SIZE][FIXED_SIZE], int board_size);
void setBoardSize(char board[FIXED_SIZE][FIXED_SIZE], int board_size);
void cleanConsole();
int getBoardSize();
int getGameplayType();
void startGame();
void restartGame();



#endif