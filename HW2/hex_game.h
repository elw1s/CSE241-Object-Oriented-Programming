#ifndef hex_game
#define hex_game


/* Library of hex_game */


#define FIXED_SIZE 12


/* Function declarations */

enum Cells{player1 = 'x', player2 = 'o', empty = '.', player1U = 'X', player2U = 'O'};



bool checkWin(char board[FIXED_SIZE][FIXED_SIZE],int current_row,int current_column,int board_size,int visited[FIXED_SIZE][FIXED_SIZE],char sign);
int charToInt(char column);
bool checkMove(char board[FIXED_SIZE][FIXED_SIZE],int column,int row);
bool checkInput(int column, int row,const int board_size);
void printBoard(char board[FIXED_SIZE][FIXED_SIZE], const int board_size);
void botTurn(char board[FIXED_SIZE][FIXED_SIZE], const int board_size);
bool playerTurn(char board[FIXED_SIZE][FIXED_SIZE],const int board_size,int gameplay_type,char sign = static_cast<char>(player1));
bool isBoardFull(char board[FIXED_SIZE][FIXED_SIZE],const int board_size);
void playerVsPlayer(char board[FIXED_SIZE][FIXED_SIZE], const int board_size,int player_turn = 0);
void initializeVisitedArray(const int board_size,int visited[FIXED_SIZE][FIXED_SIZE]);
void playerVsBot(char board[FIXED_SIZE][FIXED_SIZE], const int board_size,int player_turn = 0);
void setBoardSize(char board[FIXED_SIZE][FIXED_SIZE], const int& board_size);
void cleanConsole();
int getBoardSize(int&);
int getGameplayType(int&);
void startGame();
void restartGame();
void saveGame(const char board[FIXED_SIZE][FIXED_SIZE], const int& board_size, const std::string& file_path,const int& gameplay_type,
	const int& player_turn);
void loadGame(const std::string& file_path);



#endif