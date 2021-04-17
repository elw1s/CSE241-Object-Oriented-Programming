#ifndef hex_game
#define hex_game

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

enum HexBoard{empty = '.', user1 = 'x', user2 = 'o', bot = 'o'};

class Hex{
 private:

		class Cell{
		public:
			int row;
			char column;
			char point; 

		};
	/* private variables of Hex class */
	vector<vector<Cell> > hexCells;
	int board_size, gameplay_type; //holds size of board and type of gameplay
	bool win = false; //when win is true then game will be ended.
	static int playerMove; //static variable for counting moves of all active games.
	int user_move_x; //holds user's move of row.
	char user_move_y; //holds user's move of column.
	int index_of_column; //holds index of column
	int player_turn = 0; //if player_turn % 2 == 0 then it is the turn of user1. Same as playerMove but this variable holds only it's own object's number of moves.
	bool play_on_terminal = false; //If user wants to play on terminal then this variable will be true.
	/* private member functions of Hex class */
	int getboard_size();
	int getgameplay_type();
	void increasePlayerTurn();
	int getBoardSize();
	void setBoardSize();
	void resizeBoardSize();
	int getGameplayType();
	void playerVsPlayer();
	void playerVsBot();
	void movePlayer();
	void botTurn();
	bool checkMove(int row, int column);
	bool checkInput(int row, int column);
	char getSign();
	void setIndex_Of_Column();
	bool checkWin(int current_row, int current_column, vector<vector<int> >& visited);
	bool isBoardFull();
	void initializeVisitedVector(vector<vector<int> >& visited);
	int charToInt(char column);
	void getMove();
	void moveBot();
	int BoardSize() const;
	void PrintVisited(vector<vector<int> >& visited); // sil

 public:
 	/* public member functions of Hex class */
	Hex(int board_size);
	Hex();
	Hex(int board_size, int gameplay_type);
	void playGame();
	void printBoard();
	int numOfPlayerMoves() const;
	bool IsGameEnded() const;
	void play(char y, int x);
	void play();
	void cleanConsole();
	void playOnTerminal(bool input);
	void saveGame(const string& file_path);
	void loadGame(const string& file_path);
	static int numberOfMarkedCells();
	bool compareMarkedCells(Hex other) const;

};



#endif